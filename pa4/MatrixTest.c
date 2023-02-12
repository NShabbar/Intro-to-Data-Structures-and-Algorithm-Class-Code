//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa3
// MatrixTest.c
// A test client for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Matrix.h"
#include"List.h"

int main(int argc, char* argv[]){
	Matrix M = newMatrix(8);
	Matrix A = newMatrix(8);
	changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);

	// changeEntry Test
	//-----------------------------------------------------------------------------
	printf("Testing changeEntry() function of Matrix.c\n");
	/* changeEntry(M, 1, 2, 4);
	changeEntry(M, 1, 3, 2);
	changeEntry(M, 2, 3, 6);
	changeEntry(M, 1, 2, 0);
	changeEntry(M, 1, 2, 0); */
	changeEntry(M, 1, 1, -4);
    changeEntry(M, 1, 2, 0);
    changeEntry(M, 2, 1, 0);
    changeEntry(M, 2, 2, -2);
    changeEntry(M, 2, 4, 2);
    changeEntry(M, 3, 1, 0);
    changeEntry(M, 3, 2, 2);
    changeEntry(M, 7, 8, 5);
	
	printf("Printing Matrix M: \n");
	printMatrix(stdout, M);
	printf("\n");
	
	// size Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing size() function of Matrix.c\n");
	printf("Printing size of Matrix M: %d", size(M));
	printf("\n");
	
	// NNZ Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing NNZ() function of Matrix.c\n");
	printf("Printing NNZ of Matrix M: %d", NNZ(M));
	printf("\n");
	
	// equals Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing equals() function of Matrix.c\n");
	Matrix B = copy(M);
	fprintf(stdout, "%d", equals(M, B));
	printf("\n");
	
	
	
	// makeZero Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing makeZero() function of Matrix.c\n");
	makeZero(M);
	printMatrix(stdout, M);
	printf("\n");
	
	// transpose Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing transpose() function of Matrix.c\n");
	Matrix T = transpose(B);
	printMatrix(stdout, T);
	printf("\n");
	
	// scalarMult Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing scalarMult() function of Matrix.c\n");
	Matrix S = scalarMult(5, B);
	printMatrix(stdout, S);
	printf("\n");
	
	// sum Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing sum() function of Matrix.c\n");
	Matrix sums = sum(A, B);
	printMatrix(stdout, sums);
	printf("\n");
	
	freeMatrix(&B);
	freeMatrix(&M);
	freeMatrix(&S);
	freeMatrix(&T);
}
