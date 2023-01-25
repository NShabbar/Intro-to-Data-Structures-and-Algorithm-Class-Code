// Graph.c for CSE 101 Programming Assignment 2


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
	G -> color = calloc(n+1, sizeof(int)); // intialize color to 1 more than order.
	G -> parent = calloc(n+1, sizeof(int)); // initialize parent to 1 more than order.
	G -> dist = calloc(n+1, sizeof(int)); // initialize distance to 1 more than order.
	G -> source = NIL; // intialize source to a value below zero.
	for (int i = 0; i < n+1; i++){
		G -> adj[i] = newList(); // create list for each adjacent element.
		G -> parent[i] = NIL; // NIL because DNE yet.
		G -> dist[i] = INF; // infinity because there is no path yet.
	}
	return G; // return graph.
}

// Function freeGraph() frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
	Graph G = *pG; // pointer to G.
	for (int i = 0; i <= G -> order; i++){
		freeList(&(G -> adj[i])); // since each element is a list of adjacent lists, need to free each list.
	}
	free(G -> color); // free color node.
	free(G -> parent); // free parent node.
	free(G -> dist); // free distance node.
	*pG = NULL; // set pG to NULL.
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
	if (G -> source == NIL){ // check for if source is NIL because no parent yet created.
		return NIL;
	}
	return G -> parent[u]; // returns parent at int u.
}

// Function getDist() returns the distance from
// the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling getDist on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if (G -> source == NIL){ // checks for if source is NIL no path available so no distance.
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
	if (G -> source == NIL){ // checks for if source is NIL because if it is, then there is no path.
		fprintf(stderr, "Graph Error: calling getDist when Breadth First Search has not been done\n");
		exit(EXIT_FAILURE);
	}
	if (G -> source == u){ // append element if source is equal to that element.
		append(L, u);
	}
	else if ( G -> parent[u] == NIL){ // if parent is NIL, append NIL.
		append(L, NIL); // appends NIL.
	}else{
		getPath(L, G, G -> parent[u]); // recursive call to get path.
		append(L, u);
	}
}

/*** Manipulation procedures ***/

// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
	for (int i = 1; i <= getOrder(G); i++){ // iterate through the order of graph.
		clear (G -> adj[i]); // clear adj lists per order as it iterates.
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
	addArc(G, u, v);
	addArc(G, v, u);
}

// Function addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency 
// List of u (but not u to the adjacency List of v). 
void addArc(Graph G, int u, int v){
	if (G == NULL){ // checking precondition
		fprintf(stderr, "Graph Error: calling addArc on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	if ((getOrder(G) < v || v < 1) || (getOrder(G) < u || u <1)){ // checking precondition
		fprintf(stderr, "Graph Error: calling addArc on vertex not in range.");
		exit(EXIT_FAILURE);
	}
	if (length(G -> adj[u]) == 0){
		append(G -> adj[u], v);
	}
	moveFront(G -> adj[u]);
	while (get(G -> adj[u]) != NIL && get(G -> adj[u]) < v){
		moveNext(G -> adj[u]);
	}
	if (get(G -> adj[u]) == NIL){
		append(G -> adj[u], v);
	}
	insertBefore(G -> adj[u], v);
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
	makeNull(G); // Professor mentioned needing to clear the tree due to potential garbage so adding this here.
	G -> source = s; // set source to source since s is source.
	for (int i = 0; i <= getOrder(G); i++){
		G -> color[i] = WHITE; // set all adj elements to be WHITE.
		G -> dist[i] = INF; // set distance to INF.
		G -> parent[i] = NIL; // set parents to NIL.
	}
	G -> color[s] = GRAY; // discover the source, s, color it GRAY.
	G -> dist[s] = 0; // set distance of source to 0 since there is no path from source to source.
	G -> parent[s] = NIL; // set parent of source to NIL since source has no parent.
	List L = newList(); // create new list for BFS creation.
	append(L, s); // add source to graph.
	while (index(L) != NIL){
		int i = front(L); // get front value.
		deleteFront(L); // remove front value.
		for (int j = 0; j <= length(G -> adj[i]); j++){
			if (G -> color[j] == WHITE){
				G -> color[j] = GRAY;
				G -> dist[j] = (G -> dist[i]) + 1;
				G -> parent[j] = i;
				append(L, j);
			}
		}
		G -> color[i] = BLACK;
	}
}	

/*** Other operations ***/

// Finally, function printGraph() prints the adjacency list representation of G to the file 
// pointed to by out.
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: calling printGraph on NULL graph pointer.");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i); //print output for each order.
		moveFront(G -> adj[i]); // set cursor to front.
		printList(stdout, G -> adj[i]); // print each list.
	}
	fprintf(out, "\n");
}

