#------------------------------------------------------------------------------
#  Graph.c for CMPS 101 Programming Assignment 2
#
#                     
# 
# 
#  
#  
#------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

#define WHITE 1
#define GREY 2
#define BLACK 3

// structs --------------------------------------------------------------------


// private GraphObj type
typedef struct GraphObj{
	List *adj; // Added this because forgot these need to be matrices...
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
	G -> size = 0; // initialize size to zero.
	G -> order = n; // initialize order to n.
	G -> color = calloc(n+1, sizeof(int)); // intialize color to 1 more than order.
	G -> parent = calloc(n+1, sizeof(int)); // initialize parent to 1 more than order.
	G -> dist = calloc(n+1, sizeof(int)); // initialize distance to 1 more than order.
	G -> source = NIL; // intialize source to a value below zero.
	for (int i = 0; i < n+1; i++){
		G -> adj[i] = newList(); // create list for each matrix element.
		G -> parent[i] = NIL; // NIL because DNE yet.
		G -> dist[i] = INF; // infinity because there is no path yet.
	}
	return G;
}

// Function freeGraph() frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
	Graph G = *pG;
	for (int i = 0; i <= G -> order; i++){
		freeList(&(G -> adj[i]));
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
	if (G -> source < 0){ // checks for if source is less than 0 because no path available so no distance.
		return INF;
	}
	return G -> dist[u]; // returns distance of path to int u.
}

//Function getPath() appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u){
	if (G -> source == NIL){ // checks for if source is NIL because if it is, then there is no path.
		fprintf(stderr, "Graph Error: calling getDist when Breadth First Search has not been done\n");
		exit(EXIT_FAILURE);
	}
	if (G -> == u){
		append(L, u);
	}
	else if ( G -> parent[u] != NIL){
		getPath(L, G, G -> parent[u]);
		append(L, u);
		}
	}

/*** Manipulation procedures ***/

// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
	int null = G -> order;
	freeGraph(&G);
	G = newGraph(null);
}

// Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency 
// List of v, and v to the adjacency List of u
void addEdge(Graph G, int u, int v);

// Function addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency 
// List of u (but not u to the adjacency List of v). 
void addArc(Graph G, int u, int v);

// Function BFS() runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);

/*** Other operations ***/

// Finally, function printGraph() prints the adjacency list representation of G to the file 
// pointed to by out.
void printGraph(FILE* out, Graph G);

	
	
	
	
