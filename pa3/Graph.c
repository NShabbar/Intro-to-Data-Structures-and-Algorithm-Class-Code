//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa3
// Graph.c
// Implementation file for Graph.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

// structs --------------------------------------------------------------------


// private GraphObj type
typedef struct GraphObj{
	List *adj; // Added this because this is for adjacents.
	int *color; // Color of Node.
	int *parent; // Parent of next Node.
	int *discover // Discover time.
	int *finish // Finish time.
	int size; // Number of Edges.
	int order; // Number of Vertices.
} GraphObj;

/*** Constructors-Destructors ***/

// Function newGraph() returns a Graph pointing to a newly created GraphObj representing
// a graph having n vertices and no edges.
Graph newGraph(int n){
	if (n < 0){
		fprintf(stderr, "Graph Error: calling newGraph on negative verticies\n");
		exit(EXIT_FAILURE);
	}
	Graph G = malloc(sizeof(GraphObj)); // assign memory for size of graph G.
	G -> size = 0; // initialize size to zero since nothing in graph.
	G -> order = n; // initialize order to n.
	G -> adj = calloc(n+1, sizeof(List)); // allocate space for adj.
	G -> color = calloc(n+1, sizeof(int)); // intialize color to 1 more than order.
	G -> parent = calloc(n+1, sizeof(int)); // initialize parent to 1 more than order.
	G -> discover = calloc(n+1, sizeof(int)); // initialize discover to 1 more than order.
	G -> finish = calloc(n+1, sizeof(int)); // initialize finish time to 1 more than order.
	
	// the point of doing n+1 is to waste the first slot, something the professor mentioned
	// was recommended to do.
	for (int i = 0; i < n+1; i++){
		G -> adj[i] = newList(); // create list for each adjacent element.
		G -> parent[i] = NIL; // NIL because DNE yet.
		G -> discover[i] = UNDEF; // discover is undefined if DFS is not run.
		G -> finish[i] = UNDEF; // finish is undefined if DFS is not run.
		G -> color[i] = WHITE; // White stands for initial state of color before discovery and before DFS or BFS run.
	}
	return G; // return graph.
}

// Function freeGraph() frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
	if( pG!=NULL && *pG!=NULL ){
		for (int i = 0; i <= getOrder(*pG); i++){
			freeList(&(((*pG) -> adj)[i])); // since each element is a list of adjacent lists, need to free each list.
		}
		free(((*pG) -> adj));
		(*pG) -> adj = NULL;
		free(((*pG) -> color)); // free color node.
		(*pG) -> color = NULL;
		free(((*pG) -> parent)); // free parent node.
		(*pG) -> parent = NULL;
		free(((*pG) -> dist)); // free distance node.
		(*pG) -> dist = NULL;
		free(((*pG) -> discover)); // free discover node.
		(*pG) -> discover = NULL;
		free(((*pG) -> finish)); // free finish node.
		(*pG) -> finish = NULL;
		free(*pG);
		(*pG) = NULL; // set pG to NULL.
	}		
}

/*** Access functions ***/

//Functions getOrder() return the corresponding field values
int getOrder(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getOrder on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	return G -> order; // just need to return order.
}

// Functions getSize() return the corresponding field values
int getSize(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getSize on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	return G -> size; // just need to return size.
}

// Function getParent() will return the parent of vertex u in the DFS tree
// created by DFS(), or NIL if DFS() has not yet been called
int getParent(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getParent on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ( u < 1 || getOrder(G) < u){
		fprintf(stderr, "Graph Error: calling getParent on vertex not in range\n");
		exit(EXIT_FAILURE);
	}
	return G -> parent[u]; // returns parent at int u.
}

// Function getDiscover() will return the discover time of u in the DFS tree
// created by DFS(), or UNDEF if DFS() has not yet been called
int getDiscover(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getSource on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ( u < 1 || getOrder(G) < u){
		fprintf(stderr, "Graph Error: calling getDiscover on vertex not in range\n");
		exit(EXIT_FAILURE);
	}
	return G -> discover[u];
}

// Function getFinish() will return the finish time of u in the DFS tree
// created by DFS(), or UNDEF if DFS() has not yet been called
int getFinish(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getSource on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ( u < 1 || getOrder(G) < u){
		fprintf(stderr, "Graph Error: calling getFinish on vertex not in range\n");
		exit(EXIT_FAILURE);
	}
	return G -> finish[u];
}

/*** Manipulation procedures ***/

// Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency 
// List of v, and v to the adjacency List of u
void addEdge(Graph G, int u, int v){
	if (G == NULL){ // checking precondition
		fprintf(stderr, "Graph Error: calling addEdge on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ((getOrder(G) < v || v < 1) || (getOrder(G) < u || u <1)){ // checking precondition
		fprintf(stderr, "Graph Error: calling addEdge on vertex not in range."); // checking precondition
		exit(EXIT_FAILURE);
	}
	if ( u != v){
		addArc(G, u, v);
		addArc(G, v, u);
		G -> size--;
	}
}

// Function addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency 
// List of u (but not u to the adjacency List of v). 
void addArc(Graph G, int u, int v){
	if (G == NULL){ // checking precondition
		fprintf(stderr, "Graph Error: calling addArc on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ((getOrder(G) < v || v < 1) || (getOrder(G) < u || u < 1)){ // checking precondition
		fprintf(stderr, "Graph Error: calling addArc on vertex not in range.");
		exit(EXIT_FAILURE);
	}
	if (length(G -> adj[u]) == 0){
		append(G -> adj[u], v);
		G -> size++;
		return;
	}
	//while (index(G -> adj[u]) != NIL && get(G -> adj[u]) < v){
	moveFront(G->adj[u]);
	while(index(G -> adj[u]) != -1){
		if (v > get(G -> adj[u])){
			moveNext(G -> adj[u]);	
		}
		else if (v < get(G -> adj[u])){
			insertBefore(G -> adj[u], v);
			break;
		}
	}
	if (index(G -> adj[u]) == -1){
		append(G -> adj[u], v);
	}
	G -> size++; // Professor mentioned in lecture we needed to do size++ here. I am not too sure why. Need to ask.
}

// Function Visit()
// Helper function for DFS.
void Visit(Graph G, int x, int time){
	G -> discover[x] = time++;
	G -> color[x] = GRAY;
	moveFront(G -> adj[x]);
	for (int y = 1; y <= getOrder(G -> adj[x]); y++){
		if (color[y] == WHITE){
			G -> parent[y] = x;
			Visit(G, y, time);
		}
		moveNext(G -> adj[x]);
	}
	G -> color[x] = BLACK;
	G -> finish[x] = time++;
}

// Function DFS() runs the DFS algorithm on the Graph G with list s,
// setting the color, distance, parent, and source fields of G accordingly.
void DFS(Graph G, List S){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling DFS on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if (length(S) != getOrder(G)){
		fprintf(stderr, "Graph Error: calling DFS on list and graph not of equal length.");
		exit(EXIT_FAILURE);
	}
	for (int x = 1; x <= getOrder(G); x++){
		G -> color[x] = WHITE;
		G -> parent[x] = NIL;
	int time = 0;
	for (int x = 1; x <= getOrder(G); x++){
		if (G -> color[x] == WHITE){
			Visit(x);
	}		
}

/*** Other operations ***/

// Function transpose() returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling transpose on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	Graph t_pose = newGraph(getOrder(G));
	for (int i = 0; i <= getOrder(G); i++){
		List t_list = G -> adj[i];
		moveFront(t_list);
		while (get(t_list) != -1){
			addArc(t_pose, get(t_list), i);
			moveNext(t_list);
		}
	}
	return t_pose;
}

// copyGraph() returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling copyGraph on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	Graph copycat = newGraph(getOrder(G));
	for (int i = 0, i <= getOrder(G); i++){
		moveFront(G -> adj[i]);
		while(get(G -> adj[i]) != -1){
			addArc(copycat, i, get(G -> adj[i]));
			moveNext(G -> adj[i]);
		}
	}
	return copycat;
}

// Finally, function printGraph() prints the adjacency list representation of G to the file 
// pointed to by out.
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling printGraph on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if (out == NULL){
		fprintf(stderr, "Graph Error: calling printGraph on NULL out file.");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i); //print output for each order.
		//moveFront(G -> adj[i]); // set cursor to front.
		printList(out, G -> adj[i]); // print each list.
		fprintf(out, "\n");
	}
}

