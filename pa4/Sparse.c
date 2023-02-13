//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa4
// Sparse.c
// Implementation file for Sparse Matrix in a Matrix.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

#define MAX_LEN 300

// Helper Functions
//-----------------------------------------------------------------------------

void main(){
	return;
}
// Main Function
//-----------------------------------------------------------------------------
/* int main(int argc, char * argv[]){
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
	int n, NNZ_A, NNZ_B, row, col;
	double value;
	
	do{
		fgetc(in);
		// scan for inputs
		fscanf(in, "&d %d &d", &n, &NNZ_A, &NNZ_B);
	
		Matrix A = newMatrix(n);
		Matrix B = newMatrix(n);
	
		for (int i = 0; i <= NNZ_A; i++){
			row = fgetc(in);
			col = fgetc(in);
			value = fgetc(in);
			fscanf(in, "&d %d &d", &row, &col, &value);
			changeEntry(A, row, col, value);
		}
		for (int i = 0; i <= NNZ_B; i++){
			row = fgetc(in);
			col = fgetc(in);
			value = fgetc(in);
			fscanf(in, "&d %d &d", &row, &col, &value);
			changeEntry(B, row, col, value);
		}
	}
	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);

    fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
	
	Matrix scal = scalarMult(1.5, A);
    fprintf(out, "\n(1.5)*A =\n");
    printMatrix(out, scal);

	Matrix sums = sum(A, B);
    fprintf(out, "\nA+B =\n");
    printMatrix(out, sums);

	Matrix sums1 = sum(A, A);
    fprintf(out, "\nA+A =\n");
    printMatrix(out, sums1);

	Matrix diffs = diff(B, A);
    fprintf(out, "\nB-A =\n");
    printMatrix(out, diffs);
	
	Matrix diffs1 = diff(A, A);
    fprintf(out, "\nA-A =\n");
    printMatrix(out, diffs1);

	Matrix T = transpose(A);
    fprintf(out, "\nTranspose(A) =\n");
    printMatrix(out, T);

	Matrix prod = product(A, B);
    fprintf(out, "\nA*B =\n");
    printMatrix(out, prod);

	Matrix prod1 = product(B, B);
    fprintf(out, "\nB*B =\n");
    printMatrix(out, prod1);

    // free matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scal);
    freeMatrix(&sums);
    freeMatrix(&sums1);
    freeMatrix(&diffs);
    freeMatrix(&diffs1);
    freeMatrix(&T);
    freeMatrix(&prod);
    freeMatrix(&prod1);
	fclose(in); // close the in file.
	fclose(out); // close the out file.
	return(0);
} */
