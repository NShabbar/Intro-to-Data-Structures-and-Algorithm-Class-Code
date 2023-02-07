//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa4
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
	int column; // stores column number.
	double value; // stores float values.
} EntryObj; // name of struct.

// private MatrixObj type
typedef struct MatrixObj{
	List row; // stores lists of pointers and row number.
	int size; // stores size of matrix.
	int NNZ; // stores number of non-zeros in matrix.
} MatrixObj; // name of struct.

// Constructors-Destructors ---------------------------------------------------

// newEntry()
// Returns reference to new Entry object. Initializes column and value fields.
Entry newEntry(int n, double v){
   Entry EN = malloc(sizeof(EntryObj));
   assert( EN!=NULL );
   EN -> column = n; // entry without column.
   EN -> value = v; // entry without value.
   return(EN);
}

// freeEntry()
// Frees heap memory pointed to by *pEN, sets *pEN to NULL.
void freeEntry(Entry* pEN){
   if( pEN!=NULL && *pEN!=NULL ){
      free(*pEN);
      *pEN = NULL;
   }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	if (n < 0){
		fprintf(stderr, "Matrix Error: calling newMatrix on negative size\n");
		exit(EXIT_FAILURE);
	Matrix M = malloc(sizeof(MatrixObj)); // assign memory for size of matrix M.	
	M -> size = n; // initialize size to n.
	M -> row = calloc(n+1, sizeof(List)); // allocate space for adj.
	// the point of doing n+1 is to waste the first slot, something the professor mentioned
	// was recommended to do.
	for (int i = 0; i < n+1; i++){
		M -> row[i] = newList(); // create list for each row element.
	}
	return M; // return matrix.
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if( pM!=NULL && *pM!=NULL ){
		for (int i = 0; i <= size(*pM); i++){
			List rows = (*pM) -> row[i];
			for (moveFront(rows); 0 <= index(rows); moveNext(rows)){ // This loop exists to free all entries in the list in order to free all memory.
					Entry to_be_cleared = (Entry)get(rows);
					freeEntry(&to_be_cleared);
			}
			freeList(&(((*pM) -> row)[i])); // since each element is a list of adjacent lists, need to free each list.
		}
		free(((*pM) -> row));
		(*pM) -> row = NULL;
		free(((*pM) -> size)); // free size element.
		(*pM) -> size = NULL;
		free(((*pM) -> NNZ)); // free NNZ element.
		(*pM) -> NNZ = NULL;
		free(*pM);
		(*pM) = NULL; // set pM to NULL.
	}		
}


// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if (M == NULL){
		fprintf(stderr, "Matrix Error: calling size on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	return M -> size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if (M == NULL){
		fprintf(stderr, "Matrix Error: calling NNZ on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	return M -> NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);


// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	for (int i = 0; i <= size(M); i++){
		List rows = (M) -> row[i];
			for (moveFront(rows); 0 <= index(rows); moveNext(rows)){ // This loop exists to free all entries in the list in order to free all memory.
				Entry to_be_cleared = (Entry)get(rows);
				freeEntry(&to_be_cleared);
			}
		clear(rows); // since each element is a list of adjacent lists, need to free each list.
	}
	M -> NNZ = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);


// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if (M == NULL){
		fprintf(stderr, "Matrix Error: calling printMatrix on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	if (out == NULL){
		fprintf(stderr, "Matrix Error: calling printMatrix on NULL out file.");
		exit(EXIT_FAILURE);
	}
	/* for (int i = 1; i <= size(M); i++){
		fprintf(out, "%d */
}