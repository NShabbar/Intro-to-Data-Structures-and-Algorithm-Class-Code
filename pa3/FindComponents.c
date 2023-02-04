//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa3
// FindComponents.c
// Implementation file for Finding components in a graph.
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
	List S = newList();
	List component = newList();
	fscanf(in, "%d %d", &vertex1, &vertex2);
	while (vertex1 != 0 && vertex2 != 0){
		addArc(G, vertex1, vertex2);
		fscanf(in, "%d %d", &vertex1, &vertex2);
	}
	for( int i = 1; i <= getOrder(G); i++){
			append(S, i);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	DFS(G, S); // first DFS run.
	Graph transp = transpose(G); // transpose copied graph.
	DFS(transp, S); // second dfs graph on copied transposed graph.
	int scc_count = 0;
	for (int i = 1; i <= getOrder(G); i++){
		if (getParent(transp, i) == NIL){
			scc_count++;
		}
	}
	fprintf(out, "G contains %d strongly connected components:\n", scc_count);
	int comp_count = 0;
	for (moveBack(S); index(S) != -1; movePrev(S)){
		prepend(component, get(S));
		if(getParent(transp, get(S)) == NIL){
			comp_count++;
			fprintf(out, "Component %d: ", comp_count);
			printList(out, component);
			fprintf(out, "\n");
			clear(component);
		}
	}
	freeGraph(&G); // free graph memory.
	freeList(&S);
	freeList(&component); // free path list.
	fclose(in); // close the in file.
	fclose(out); // close the out file.
	return(0);
}
