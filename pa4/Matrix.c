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
#include "Matrix.h"

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
	List* row; // stores lists of pointers and row number.
	int size; // stores size of matrix.
	int NNZ; // stores number of non-zeros in matrix.
} MatrixObj; // name of struct.


// Helper Functions -----------------------------------------------------------

// function to sort entryies in order.
void InsertInOrder(Matrix M, List rows, int col, double x); // Helper function to be used in ChangedEntry.
void freeEntry(Entry* pEN); // Helper function to free Entry struct.
Entry newEntry(int n, double v); // Helper function to make new Entry struct.

void InsertInOrder(Matrix M, List rows, int col, double x){
	for (moveFront(rows); 0 <= index(rows); moveNext(rows)){ // step through indices of list.
		Entry rowcol = (Entry)get(rows); 
		if ((rowcol -> column) == col){
			if (x != 0){ // if value is not zero, but column exists, overwrite.
				(rowcol -> value) = x; // replaces the value of the entry.
			}else{ // if x = 0, free entry, delete in row, and reduce nonzero.
				freeEntry(&rowcol);
				delete(rows);
				M -> NNZ--;
			}
			return;
		}
		if (col < (rowcol -> column)){ // sorts in order of columns.
			if (x != 0){ // if value is not zero, creates new entry, inserts, and then increases nonzero.
				Entry new = newEntry(col, x);
				insertBefore(rows, new);
				M -> NNZ++;
			}
			return;
		}	
	}
	if (index(rows) == -1){ // if reach end of list, and column not found, make new entry, append, then add nonzero.
		if (x != 0){ // if value is not zero, creates new entry, inserts, and then increases nonzero.
			Entry new = newEntry (col, x);
			append(rows, new);
			M -> NNZ++;
		}
	}
	return;
}
	
			

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
	}
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
int equals(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "Matrix Error: calling equals on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	if (size(A) != size(B)){ // if size of matrices are not the same, return false.
		return false;
	}
	for (int i = 1; i <= size(A); i++){ // since matrices must be same size, doesn't matter which matrix we index.
		if (length(A -> row[i]) != length(B -> row[i])){ // if length of rows are not the same, return false.
			return false;
		}
		List Arows = A -> row[i]; // create variable for list of row.
		List Brows = B -> row[i]; // create variable for list of row.
		moveFront(Arows); // set to front of list.
		moveFront(Brows); // set to front of list.
		while (index(Arows) > -1 && index(Brows) > -1){ // As long as index does not reach -1, step through entries and compare.
			Entry colA = (Entry)get(Arows);
			Entry colB = (Entry)get(Brows);
			if ((colA -> column) != (colB -> column) || (colA -> value) != (colB -> value)){ // if column or value are not equal, return false.
				return false;
			}
			moveNext(Arows);
			moveNext(Brows);
		}
	}
	return true;
}


// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	if (M == NULL){
		fprintf(stderr, "Matrix Error: calling makeZero on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
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
void changeEntry(Matrix M, int i, int j, double x){
	if (M == NULL){
		fprintf(stderr, "Matrix Error: calling changeEntry on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	if (i > size(M) || j > size(M) || i < 1 || j < 1){
		fprintf(stderr, "Matrix Error: calling changeEntry on values larger than matrix size.");
		exit(EXIT_FAILURE);
	}
	List rows = M -> row[i];
	InsertInOrder(M, rows, j, x); // helper function sorts and takes care of all matrix values too.
}


// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	if (A == NULL){
		fprintf(stderr, "Matrix Error: calling copy on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	Matrix copycat = newMatrix(size(A)); // create new matrix the size of matrix we want to copy.
	for (int i = 1; i <= size(A); i++){
		List Arows = A -> row[i];
		moveFront(Arows);
		while(index(Arows) != -1){
			Entry temp = (Entry)get(Arows);
			changeEntry(copycat, i, temp -> column, temp -> value); // add values from matrix A to new matrix.
			moveNext(Arows);
		}
	}
	return copycat;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if (A == NULL){
		fprintf(stderr, "Matrix Error: calling transpose on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	Matrix transMat = newMatrix(size(A)); // create new matrix the size of matrix we want to transpose.
	for (int i = 1; i <= size(A); i++){
		List Arows = A -> row[i];
		moveFront(Arows);
		while(index(Arows) != -1){
			Entry temp = (Entry)get(Arows);
			changeEntry(transMat, temp -> column, i, temp -> value); // same concept as copy, but row and column are swapped.
			moveNext(Arows);
		}
	}
	return transMat;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if (A == NULL){
		fprintf(stderr, "Matrix Error: calling scalarMult on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	Matrix scalar = newMatrix(size(A));
	for (int i = 1; i <= size(A); i++){
		List Arows = A -> row[i];
		moveFront(Arows);
		while(index(Arows) != -1){
			Entry temp = (Entry)get(Arows);
			double newval = (temp -> value) * x;
			temp -> value = newval;
			changeEntry(scalar, i, temp -> column, temp -> value);
			moveNext(Arows);
		}
	}
	return scalar;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	return;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	return;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){ // transpose B, multiply in values of both after.
	if (A == NULL || B == NULL){
		fprintf(stderr, "Matrix Error: calling product on NULL matrix pointer.");
		exit(EXIT_FAILURE);
	}
	if (size(A) != size(B)){ // if size of matrices are not the same, return false.
		fprintf(stderr, "Matrix Error: calling product on Matrices of differing sizes.");
		exit(EXIT_FAILURE);
	}
	Matrix prod = newMatrix(size(A));
	Matrix transB = transpose(B);
	for (int i = 1; i <= size(A); i++){
		List Arows = A -> row[i];
		List Brows = transB -> row [i];
		moveFront(Arows);
		moveFront(Brows);
		while(index(Arows) != -1){
			Entry tempA = (Entry)get(Arows);
			Entry tempB = (Entry)get(Brows);
			double newval = (tempA -> value) * (tempB -> value);
			tempB -> value = newval;
			if (newval != 0){
				changeEntry(prod, i, tempA -> column, tempB -> value);
			}
			moveNext(Arows);
			moveNext(Brows);
		}
	}
	freeMatrix(&transB);
	return prod;
}

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
	for (int i = 1; i <= size(M); i++){
		List rows = M -> row[i];
		moveFront(rows);
		fprintf(out, "%d: ", i);
		while( index(rows) > -1){
			Entry col = (Entry)get(rows);
			if (!length(rows)){
				continue;
			}
			if (col -> value != 0){
				fprintf(out, "(%d, %.1f)", col -> column, col -> value);
			}
			moveNext(rows);
		}
		fprintf(out, "\n");
	}
}