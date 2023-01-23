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
	int *color; // Color of Node.
	int *parent; // Parent of next Node.
	int *dist; // Distance
	int size;
	int order;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/

// Function newGraph() returns a Graph pointing to a newly created GraphObj representing
// a graph having n vertices and no edges.
Graph newGraph(int n){
	if (n < 0){
		fprintf(stderr, "Graph Error: calling newGraph on negative verticies\n");
	}
	Graph GRAPH = malloc(sizeof(GraphObj)); // assign memory for size of graph GRAPH.
	GRAPH -> size = 0; // initialize size to zero.
	GRAPH -> order = n; // initialize order to n.
	GRAPH -> color = calloc(n+1, sizeof(int)); // intialize color to 1 more than order.
	GRAPH -> parent = calloc(n+1, sizeof(int)); // initialize parent to 1 more than order.
	
	
	
	
