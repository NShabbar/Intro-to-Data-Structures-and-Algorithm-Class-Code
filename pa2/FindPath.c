//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa2
// FindPath.c
// Implementation file for Finding Path in a graph.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

// Helper Functions
//-----------------------------------------------------------------------------


// Main Function
//-----------------------------------------------------------------------------
int main(int argc, char * argv[]){
	FILE *in, *out;
	// Check command line for correct number of arguments
	if (argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	// Open files for reading and writing
	in = fopen(argv[1], "r"); // Opens and reads input file.
	if (in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w"); //Opens and writes to output file.
	if (out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	int n, edge1, edge2;
	fscanf(in, " %d", &n); // scanning for n size.
	Graph G = newGraph(n); // create a new graph with size n.
	List dist = newList();
	List source = newList();
	List path = newList();
	fscanf(in, " %d", &edge1); // add an edge arg.
	fscanf(in, " %d", &edge2); // add a second edge arg.
	while (edge1 != 0 && edge2 != 0){
		addEdge(G, edge1, edge2);
		append(source, edge1);
		append(dist, edge2);
		fscanf(in, " %d", edge1); // add an edge arg.
		fscanf(in, " %d", &edge2); // add a second edge arg.
	}
	printGraph(out, G);
	while (length(source) != 0){
		fprintf(out, "\n");
		edge1 = front(source);
		deleteFront(source);
		edge2 = front(dist);
		deleteFront(dist);
		BFS(G, edge1);
		clear(path);
		getPath(path, G, edge2);
		if (front(path) == NIL){
			fprintf(out, "No path from %d to %d exists\n", edge1, edge2);
			fprintf(out, "The distance from %d to %d is therefore infinity\n", edge1, edge2);
		}else{
			fprintf(out, "The distance from %d to %d is %d\n", edge1, edge2, getDist(G, edge2));
			fprintf(out, "A shortest path from %d to %d is: ", edge1, edge2);
			printList(out, path);
			fprintf(out, "\n");
		}
	} 
	freeGraph(&G); // free graph memory.
	freeList(&path); // free path list.
	freeList(&source); // free first edge list.
	freeList(&dist); // free second edge list.
	fclose(in); // close the in file.
	fclose(out); // close the out file.
	return(0);
}