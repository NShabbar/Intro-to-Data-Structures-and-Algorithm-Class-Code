//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
	ListElement data;
	Node next;
	Node previous;
} NodeObj;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(QueueElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N -> data = data;
   N -> next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty list object.
List newList(){
	List L;
	L = malloc(sizeof(ListObj));
	assert(L! = NULL);
	L -> front = L -> back = NULL;
	L -> length = 0;
	return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
	if (pL != NULL && *pL != NULL){
		while (!isEmpty(*pL)){
			Dequeue(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

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


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element's data with x. Pre: length() > 0, index() >= 0.
void set(List L, int x);

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L;
// If cursor is defined and at front, cursor becomes undefined;
// If cursor is undefined, do nothing.
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L;
// If cursor is defined and at the back, cursor becomes undefined;
// If cursor is undefined, do nothing.
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x);

// append()
// Insert new element into L. If L is non-empty, insertion takes place after the back element.
void append(List L, int x);

// insertBefore()
// Insert new element before cursor. Pre: length() > 0, index() >= 0.
void insertBefore(List L, int x);

// insertAfter()
// Insert new element after cursor. Pre: length() > 0, index() >= 0.
void insertAfter(List L, int x);

// deleteFront()
// Delete the front element. Pre: length() > 0.
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length() > 0.
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. Pre: length() > 0, index() >= 0.
void delete(List L);


// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of
// a space separated sequence of integers, with front on left.
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L);

// Extra Credit operation ------------------------------------------------------

//concatList()
// Returns a new List which is the concatenation of A and B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);