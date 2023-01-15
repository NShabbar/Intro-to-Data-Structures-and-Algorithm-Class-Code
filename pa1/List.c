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
	Node cursor;
	int index;
	int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N -> data = data;
   N -> next = NULL;
   N -> previous = NULL;
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
	L -> cursor = NULL;
	L -> index = -1;
	L -> length = 0;
	return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
	if (pL != NULL && *pL != NULL){
		while (length(*pL) > 0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L){
	if ( L == NULL){
		printf("List Error: Calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return(L -> length);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
	if (L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		return(-1);
	}
	return L -> index;
}

// front()
// Returns front element of L. Pre: length() > 0
int front(List L){
	if (L == NULL){
		printf("List Error: Calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: Calling front() on an empty List\n");
	}
	return(L -> front -> data);
}

// back()
// Returns front element of L. Pre: length() > 0
int back(List L){
	if (L == NULL){
		printf("List Error: Calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: Calling back() on an empty List\n");
	}
	return(L -> back -> data);
}
// get()
// Returns cursor element of L. Pre: length() > 0, index() >= 0
int get(List L){
	if (L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: calling get() on empty List\n");
	}
	if (L -> cursor == NULL){
		printf("List Error: calling get() not possible if cursor is undefined\n");
	}
	return(L -> cursor -> data;);
}

// equals()
//Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B){
	if (A == NULL || B == NULL){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	bool eq;
	Node N, M;
	eq = (A -> length == B -> length);
	N = A -> front;
	M = B -> front;
	while (eq && N != NULL){
		eq = (N -> data == M -> data);
		N = N -> next;
		M = M -> next;
	}
	return eq;
}

/* // isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L){
	if (L == NULL){
		printf("List Error: Calling isEmpty() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return(L -> length == 0);
}

 */
// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L){
	if (L == NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	while(length(L) > 0){
		deleteFront(L);
	}
	L -> front = NULL;
	L -> back = NULL;
	L -> cursor = NULL;
	L -> length = 0;
	L -> index = -1;
}

// set()
// Overwrites the cursor element's data with x. Pre: length() > 0, index() >= 0.
void set(List L, int x){
	Node N = newNode(x);
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
	if (L == NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0){
		L -> cursor = L -> front;
		L -> index = 0;
	}
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
	if (L == NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0){
		L -> cursor = L -> back;
		L -> index = L -> length - 1;
	}
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L;
// If cursor is defined and at front, cursor becomes undefined;
// If cursor is undefined, do nothing.
void movePrev(List L){
	if (L == NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor == L -> front){
		L -> cursor = NULL;
		L -> index = -1;
	}else{
		L -> cursor = L -> cursor -> previous;
		L -> index--;
	}
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L;
// If cursor is defined and at the back, cursor becomes undefined;
// If cursor is undefined, do nothing.
void moveNext(List L){
	if (L == NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor == L -> back){
		L -> cursor = NULL;
		L -> index = -1;
	}else{
		L -> cursor = L -> cursor -> next;
		L -> index++;
	}
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x){
	Node N = newNode(x);
	if (L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> front == NULL){
		L -> front = L -> back = N;
		L -> cursor = L -> front;
	}else{
		L -> front -> previous = N;
		N -> next = L -> front;
		L -> front = N;
		L -> index++;
	}
	L -> length++;
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after the back element.
void append(List L, int x);
	Node N = newNode(x);
	if (L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> == NULL){
		L -> back = L -> front = N;
		L -> cursor = L -> back;
	}else{
		L -> back -> next = N;
		N -> previous = L -> back;
		L -> back = N;
		N -> next = NULL;
	}
	L -> length++;
}

// insertBefore()
// Insert new element before cursor. Pre: length() > 0, index() >= 0.
void insertBefore(List L, int x){
	Node N = newNode(x);
	if (L == NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor == NULL){
		printf("List Error: calling insertBefore not possible if cursor is undefined\n");
	}
	if (L -> cursor == L -> front){
		prepend(L, x);
	}else{
		N -> previous = L -> cursor -> previous;
		N -> next = L -> cursor;
		L -> cursor -> previous -> next = N;
		L -> cursor -> previous = N;
		L -> index++;
		L -> length++;
	}
}

// insertAfter()
// Insert new element after cursor. Pre: length() > 0, index() >= 0.
void insertAfter(List L, int x){
	Node N = newNode(x);
	if (L == NULL){
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor == NULL){
		printf("List Error: calling insertAfter not possible if cursor is undefined\n");
	}
	if (length(L) <= 0){
		printf("List Error: calling insertAfter on an empty List\n");
	}
	if (L -> cursor == L -> back){
		append(L, x);
	}else{
		N -> next = L -> cursor -> next;
		N -> previous = L -> cursor;
		L -> cursor -> next -> previous = N;
		L -> cursor -> next = N;
		L -> length++;
	}
}

// deleteFront()
// Delete the front element. Pre: length() > 0.
void deleteFront(List L){
	Node N = NULL;
	if (L == NULL){
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: calling deleteFront() on empty List\n");
	}else{
		if (L -> length == 1){
			N = L -> front;
			freeNode(&N);
			L -> front = L -> back = NULL;
			L -> cursor = NULL;
			L -> index = -1;
		}else{
			N = L -> front;
			L -> front = L -> front -> next;
			L -> front -> previous = NULL;
			if (L -> cursor != NULL){
				L -> index--;
			}
			freeNode(&N);
		}
		L -> length--;
	}
}

// deleteBack()
// Delete the back element. Pre: length() > 0.
void deleteBack(List L);
	Node N = NULL;
	if (L == NULL){
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: calling deleteBack() on empty List\n");
	}else{
		if (L -> length == 1){
			N = L -> back;
			freeNode(&N);
			L -> back = L -> front = NULL;
			L -> cursor = NULL;
			L -> index = -1;
		}else{
			N = L -> back;
			L -> back = L -> back -> previous;
			L -> back -> next = NULL;
			if (L -> index == L -> length - 1){
				L -> index = -1;
			}
			freeNode(&N);
		}
		L -> length--;
	}
}

// delete()
// Delete cursor element, making cursor undefined. Pre: length() > 0, index() >= 0.
void delete(List L){
	Node N = NULL;
	if (L == NULL){
		printf("List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: calling delete() on empty List\n");
	}
	if (L -> cursor == NULL){
		printf("List error: calling delete() not possible if cursor is undefined\n");
	}
	if (L -> cursor == L -> front){
		deleteFront(L);
	}
	if (L -> cursor == L -> back){
		deleteBack(L);
	}else{
		N = L -> cursor;
		L -> cursor -> previous -> next = L -> cursor -> next;
		L -> cursor -> next -> previous = L -> cursor -> previous;
		freeNode(&N);
		L -> length--;
	}
	L -> index = -1;
}

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of
// a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	Node N = NULL;
	if (L == NULL){
		printf("List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	for (N = L -> front; N != NULL; N = N -> next){
		printf(FORMAT" ", N -> data);
	}
	printf("\n");
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L){
	Node N = NULL;
	List dup_list = newList();
	if (length(L) > 0){
		N = L -> front;
		while (N != NULL){
			append(dup_list, N -> data);
			N = N -> next;
		}
	}
	dup_list -> cursor = NULL;
	dup_list -> index = -1;
	return(dup_list);
}
	/* struct Node* current = L; // Used to iterate over the original list.
	struct Node* newList = NULL; // Beginning of the new list.
	struct Node* tail = NULL; // Point to the last node in a new list.
	
	while( current != NULL){
		if (newList == NULL){ // For the first new node.
			newList = (struct Node*)malloc(sizeof(struct Node));
			newList -> data = current -> data;
			newList -> next = NULL;
			tail = newList;
		}
		else{
			tail -> next = (struct Node*)malloc(sizeof(struct Node));
			tail = tail -> next;
			tail -> data = current -> data;
			tail -> next = Null;
		}
		current = current -> next;
	}
	return newList;
} */


// Extra Credit operation ------------------------------------------------------

//concatList()
// Returns a new List which is the concatenation of A and B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);
