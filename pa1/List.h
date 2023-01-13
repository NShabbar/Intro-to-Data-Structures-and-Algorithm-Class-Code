//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>

// Exported types -------------------------------------------------------------
typedef int ListElement;
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty list object.
List newList();

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// front()
// Returns front element of L. Pre: length() > 0
int front(List L);

// back()
// Returns front element of L. Pre: length() > 0
int back(List L);

// get()
// Returns front element of L. Pre: length() > 0, index() >= 0
int get(List L);

// equals()
//Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B);

