//-----------------------------------------------------------------------------
// Lex.c
// Implementation file for Lex sorting.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300;

int main(int argc, char * argv{}){
	
	int token_count, line_count;
	FILE *in, *out;
	char line[MAX_LEN];
	char tokenBuffer[MAX_LEN];
	char* token;
	
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
	
	// Read each line of input file, then count and print tokens
	line_count = 0;
	
	while (fgets(line, MAX_LEN, in) != NULL){
		line_count++;
	}
	
	rewind(in);
	
	token = malloc((line_count) * sizeof(char*));
	
	for (int i = 0; i < line_count; i++){
		token = malloc((MAX_LEN) * sizeof(char)); 
	}
	
	token_count = 0;
	
	while (fgets(line, sizeof(line), in) != NULL)){
		strcpy(token[token_count], line);
		token_count++;
	}
	
	List A = newList();
	append(list, 0);
	
	for (int i = 1; i < line_count; i++){
		moveFront(A);
		char* element = token[i];
		int comp_count = i;
		while (comp_count > 0 && strcmp(element, token(get(A)]) >= 0){
			moveNext(A);
			comp_count--;
		}
		if (index(A) >=0){
			insertBefore(A, i);
		}else{
			append(A, i);
		}
	}
	
	moveFront(A);
	
	while (index(A) >= 0){
		fprintf(out, "%s", token[get(A)]);
		moveNext(A);
	}
	
	// Close files
	fclose(in);
	fclose(out);
	
	freeList(&A);
	
	for (int i = 0; i < line_count; i++){
		free(token[i]);
	}
	
	free(token);
	return(0);
}
