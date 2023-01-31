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
	int *dist; // Distance.
	int *discover // Discover time.
	int *finish // Finish time.
	int size; // Number of Edges.
	int order; // Number of Vertices.
	int source; // Label for Vertex most recently used.
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
	G -> dist = calloc(n+1, sizeof(int)); // initialize distance to 1 more than order.
	G -> discover = calloc(n+1, sizeof(int)); // initialize discover to 1 more than order.
	G -> finish = calloc(n+1, sizeof(int)); // initialize finish time to 1 more than order.
	G -> source = NIL; // intialize source to a value below zero.
	
	// the point of doing n+1 is to waste the first slot, something the professor mentioned
	// was recommended to do.
	for (int i = 0; i < n+1; i++){
		G -> adj[i] = newList(); // create list for each adjacent element.
		G -> parent[i] = NIL; // NIL because DNE yet.
		G -> dist[i] = INF; // infinity because there is no path yet.
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

// getSource() returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getSource on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if (G -> source == NIL){ // if source is NIL, return NIL.
		return NIL;
	}
	return G -> source; // just need to return source.
}

// Function getParent() will return the parent of vertex u in the BFS tree
// created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getParent on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ( u < 1 || getOrder(G) < u){
		fprintf(stderr, "Graph Error: calling getParent on vertex not in range\n");
		exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){ // check for if source is NIL because no parent yet created.
		return NIL;
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

// Function getDist() returns the distance from
// the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getDist on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ( u < 1 || getOrder(G) < u){
		fprintf(stderr, "Graph Error: calling getDist on vertex not in range\n");
		exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){ // checks for if source is NIL no path available so no distance.
		return INF;
	}
	return G -> dist[u]; // returns distance of path to int u.
}

//Function getPath() appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getPath on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){ // checks for if source is NIL because if it is, then there is no path.
		fprintf(stderr, "Graph Error: calling getPath when Breadth First Search has not been done\n");
		exit(EXIT_FAILURE);
	}
	if ( u < 1 || getOrder(G) < u){
		fprintf(stderr, "Graph Error: calling getDist on vertex not in range\n");
		exit(EXIT_FAILURE);
	}
	if (getSource(G) == u){ // append element if source is equal to that element.
		append(L, u);
	}
	else if (getParent(G, u) == NIL){ // if parent is NIL, append NIL.
		append(L, NIL); // appends NIL.
	}else{
		getPath(L, G, getParent(G, u)); // recursive call to get path.
		append(L, u);
	}
}

/*** Manipulation procedures ***/

// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
	for (int i = 0; i < getOrder(G); i++){ // iterate through the order of graph.
		clear(G -> adj[i]); // clear adj lists per order as it iterates.
		G -> color[i] = WHITE;
		G -> parent[i] = NIL;
		G -> dist[i] = INF;
	}
	G -> size = 0; // set size to zero, since graph should be empty.
}

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

// Function BFS() runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling BFS on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if (getOrder(G) < s || s < 1){
		fprintf(stderr, "Graph Error: calling BFS on vertex not in range.");
		exit(EXIT_FAILURE);
	}
	G -> source = s; // set source to source since s is source.
	for (int i = 1; i <= getOrder(G); i++){
		G -> color[i] = WHITE; // set all adj elements to be WHITE.
		G -> dist[i] = INF; // set distance to INF.
		G -> parent[i] = NIL; // set parents to NIL.
	}
	G -> color[s] = GRAY; // discover the source, s, color it GRAY.
	G -> dist[s] = 0; // set distance of source to 0 since there is no path from source to source.
	G -> parent[s] = NIL; // set parent of source to NIL since source has no parent.
	List L = newList(); // create new list for BFS creation.
	append(L, s); // add source to graph.
	while (length(L) != 0){
		int x = front(L); // get front value.
		deleteFront(L); // remove front value.
		if(length(G -> adj[x]) != 0){		
			for (moveFront(G -> adj[x]); index(G -> adj[x]) != -1; moveNext(G -> adj[x])){
				int j = get(G -> adj[x]);
				if (G -> color[j] == WHITE){
					G -> color[j] = GRAY;
					G -> dist[j] = G -> dist[x] + 1;
					G -> parent[j] = x;
					append(L, j);
				}
			}
		}
		G -> color[x] = BLACK;
	}
	freeList(&L);
}	

// Function DFS() runs the DFS algorithm on the Graph G with list s,
// setting the color, distance, parent, and source fields of G accordingly.
void DFS(Graph G, List S);

/*** Other operations ***/

// Function transpose() returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// copyGraph() returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G);

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

