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
	int n, vertex1, vertex2;
	fscanf(in, " %d", &n); // scanning for n size.
	Graph G = newGraph(n); // create a new graph with size n.
	List path = newList();
	fscanf(in, "%d %d", &vertex1, &vertex2);
	while (vertex1 != 0 && vertex2 != 0){
		addEdge(G, vertex1, vertex2);
		//fscanf(in, " %d", &edge1); // add an edge arg.
		//fscanf(in, " %d", &edge2); // add a second edge arg.
		fscanf(in, "%d %d", &vertex1, &vertex2);
	}
	printGraph(out, G);
	fscanf(in, "%d %d", &vertex1, &vertex2);
	while (vertex1 != 0 && vertex2 != 0){
		fprintf(out, "\n");
		BFS(G, vertex1);
		clear(path);
		getPath(path, G, vertex2);
		
		if (front(path) == NIL){
			fprintf(out, "The distance from %d to %d is infinity\n", vertex1, vertex2);
			fprintf(out, "No %d-%d path exists\n", vertex1, vertex2);
		}else{
			fprintf(out, "The distance from %d to %d is %d\n", vertex1, vertex2, getDist(G, vertex2));
			fprintf(out, "A shortest %d-%d path is: ", vertex1, vertex2);
			printList(out, path);
			fprintf(out, "\n");
		}
		fscanf(in, "%d %d", &vertex1, &vertex2);
	} 
	freeGraph(&G); // free graph memory.
	freeList(&path); // free path list.
	fclose(in); // close the in file.
	fclose(out); // close the out file.
	return(0);
}