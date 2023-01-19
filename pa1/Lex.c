//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa1
// Lex.c
// Implementation file for Lex sorting.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

// Helper Functions
//-----------------------------------------------------------------------------

List insertSort(char** A, int num_count){ //Takes array and number input.
	int item;
	List work_list = newList();
	
	// append the first element to start.
	if (num_count > 0){
		append(work_list, 0);
	}
	for (item = 1; item < num_count; item++){
		char *temp_node = A[item];
		moveFront(work_list); // Start index at front, which should be zero.
		while (index(work_list) != -1 && strcmp(temp_node, A[get(work_list)]) > 0){ // Compare strings
			moveNext(work_list);
		}
		if (index(work_list) == -1){
			append(work_list, item);
		}else{
			insertBefore(work_list, item);
		}
	}
	return work_list;
}

// Duplicating the String.
char *strdup (const char *str){ // String that is desired to be copied.
	char *dup = malloc(strlen(str) + 1); // Assign memory of string length + 1 to accommodate null char.
	if (dup == NULL){
		return NULL;
	}
	strcpy(dup, str); // Copies a duplicate from string.
	return dup;
}

// Read file into array, then uses the duplicate func to dup.
char** read(FILE* in, int line_number){ // Takes file input and number of lines to read.
	char** file_array = calloc(line_number, sizeof(char**)); // Create memory for array size.
	char line[MAX_LEN]; // Buffer
	for (int count = 0; count < line_number; count++){ // Reads through lines until all lines read.
		fgets(line, MAX_LEN, in); // Retrieves line from input file.
		file_array[count] = strdup(line); // Creates duplicate of array.
	}
	return file_array;
}

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
	
	// Read each line of input file, then count and print tokens
	line_count = 0;
	
	while (fgets(line, MAX_LEN, in) != NULL){
		line_count++;
	}

	rewind(in);
	
	//token = malloc((line_count) * sizeof(char*));
	token = read(in, line_count);
	
	List L = insertSort(token, line_count);
	moveFront(L);
	
	for (int i = 0; i < line_count; i++){
		fprintf(out, "%s", token[get(L)]);
		moveNext(L); 
	}
	
	// Close files
	fclose(in);
	fclose(out);
	
	for (int i = 0; i < line_count; i++){
		free(token[i]);
	}
	
	free(token);
	freeList(&L);
	return(0);
}

 