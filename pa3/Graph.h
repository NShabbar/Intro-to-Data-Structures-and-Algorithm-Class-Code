//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa3
// Graph.h
// Header file for Graph.c.
//-----------------------------------------------------------------------------
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include<stdbool.h>
#include "List.h"

#define INF -1 // Any negative number works.
#define NIL -2 // Any negative number works, but must be different than INF.
#define UNDEF -3 // Any negative number works, but must be different than INF and NIL.

// Exported types -------------------------------------------------------------
typedef int GraphElement;
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// Function newGraph() returns a Graph pointing to a newly created GraphObj representing
// a graph having n vertices and no edges.
Graph newGraph(int n);

// Function freeGraph() frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG);

/*** Access functions ***/

//Functions getOrder() return the corresponding field values
int getOrder(Graph G);

// Functions getSize() return the corresponding field values
int getSize(Graph G);

// Function getParent() will return the parent of vertex u in the BFS tree
// created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u);

// Function getDiscover() will return the discover time of u in the DFS tree
// created by DFS(), or UNDEF if DFS() has not yet been called
int getDiscover(Graph G, int u);

// Function getFinish() will return the finish time of u in the DFS tree
// created by DFS(), or UNDEF if DFS() has not yet been called
int getFinish(Graph G, int u);


/*** Manipulation procedures ***/

// Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency 
// List of v, and v to the adjacency List of u
void addEdge(Graph G, int u, int v);

// Function addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency 
// List of u (but not u to the adjacency List of v). 
void addArc(Graph G, int u, int v);

// Function Visit()
// Helper function for DFS.
void Visit(Graph G, List L, int x);

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
void printGraph(FILE* out, Graph G);

#endif