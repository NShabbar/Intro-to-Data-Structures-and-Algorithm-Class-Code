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
	}
	Graph G = malloc(sizeof(GraphObj)); // assign memory for size of graph G.
	G -> size = 0; // initialize size to zero.
	G -> order = n; // initialize order to n.
	G -> color = calloc(n+1, sizeof(int)); // intialize color to 1 more than order.
	G -> parent = calloc(n+1, sizeof(int)); // initialize parent to 1 more than order.
	G -> dist = calloc(n+1, sizeof(int)); // initialize distance to 1 more than order.
	G -> source = NIL; // intialize source to a value below zero.
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
int getOrder(Graph G);

// Functions getSize() return the corresponding field values
int getSize(Graph G);

// getSource() returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G);

// Function getParent() will return the parent of vertex u in the BFS tree
// created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u);

// Function getDist() returns the distance from
// the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u);

//Function getPath() appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

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

	
	
	
	
