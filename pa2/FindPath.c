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
	
	int line_count;
	FILE *in, *out;
	char line[MAX_LEN];
	//char tokenBuffer[MAX_LEN];
	char** token;
	
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
/* 
	free(token);
	freeGraph(&G); */
	return(0);
}