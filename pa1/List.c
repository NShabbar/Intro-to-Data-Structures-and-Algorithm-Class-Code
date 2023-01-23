//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa1
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
   N -> data = data; // new data we want to add.
   N -> next = NULL; // node without next element.
   N -> previous = NULL; // node without previous element.
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
	assert(L != NULL);
	L -> front = L -> back = NULL;
	L -> cursor = NULL; // sets cursor as undefined.
	L -> index = -1; // sets cursor index as undefined.
	L -> length = 0; // initialize list with nothing
	return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){	
	if (pL != NULL && *pL != NULL){
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L){
	if ( L == NULL){
		fprintf(stderr, "List Error: Calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return(L -> length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		return(-1); // empty list, returns undefined cursor.
	}
	if (L -> cursor == NULL){
		return(-1);
	}
	return L -> index;
}

// front()
// Returns front element of L. Pre: length() > 0
int front(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		printf("List Error: Calling front() on an empty List\n");
	}
	return(L -> front -> data);
}

// back()
// Returns back element of L. Pre: length() > 0
int back(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling back() on NULL List reference\n");
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
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		fprintf(stderr, "List Error: calling get() on empty List\n");
	}
	if (L -> cursor == NULL){
		fprintf(stderr, "List Error: calling get() not possible if cursor is undefined\n");
	}
	return(L -> cursor -> data);
}

// equals()
//Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
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
		fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	while(length(L) > 0){
		deleteFront(L);
	}
	L -> front = NULL;
	L -> back = NULL;
	L -> cursor = NULL; // sets cursor as undefined.
	L -> length = 0; // value length of an empty list.
	L -> index = -1; // sets cursor index as undefined.
}

// set()
// Overwrites the cursor element's data with x. Pre: length() > 0, index() >= 0.
void set(List L, int x){
	if (L == NULL){
		fprintf(stderr, "List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		fprintf(stderr, "List Error: calling set() on an empty set\n");
	}
	(L -> cursor) -> data = x; // change data of node. () important because without them, it will change node itself.
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0){
		L -> cursor = L -> front; // place cursor to front of list.
		L -> index = 0; // sets cursor index to front position of list.
	}
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0){
		L -> cursor = L -> back; // place cursor to the back of list.
		L -> index = L -> length - 1; // sets cursor index to the back position of list.
	}
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L;
// If cursor is defined and at front, cursor becomes undefined;
// If cursor is undefined, do nothing.
void movePrev(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor == L -> front){ // checking for special case where cursor is at front and therefore cause cursor to be undefined.
		L -> cursor = NULL; // sets cursor to undefined.
		L -> index = -1; // set the cursor index as undefined.
	}else{
		L -> cursor = L -> cursor -> previous; // set cursor to previous item.
		L -> index--; // decrement index value.
	}
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L;
// If cursor is defined and at the back, cursor becomes undefined;
// If cursor is undefined, do nothing.
void moveNext(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor == L -> back){ // checking for special case where cursor is at the back and therefore cause cursor to be undefined.
		L -> cursor = NULL; // set the cursor as undefined.
		L -> index = -1; // set the cursor index as undefined.
	}else{
		L -> cursor = L -> cursor -> next; // sets cursor to next item.
		L -> index++; // increment index value.
	}
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x){
	Node N = newNode(x);
	if (L == NULL){
		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> cursor != NULL){
		L -> index++; //increment index value.
	}
	if (length(L) <= 0){
		L -> front = L -> back = N; // because front is NULL, set front and back = then set them to N element.
	}else{
		L -> front -> previous = N; // define "old" front to point to previous which is new N element.
		N -> next = L -> front; // points N element next item to "old" front item.
		L -> front = N; // front is now new N element.
	}
	L -> length++; // increment list length.
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after the back element.
void append(List L, int x){
	Node N = newNode(x);
	if (L == NULL){
		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		L -> back = L -> front = N; // since the back of the list is Null, front is too. Set both to N element.
	}else{
		L -> back -> next = N; // define "old" back as pointing to next which is new N element.
		N -> previous = L -> back; // repoint previous item as the old "back" item.
		L -> back = N; // add N element to back of list.
		N -> next = NULL; // since adding to back of the list, need to make next NULL again.
	}
	L -> length++; // increment list length.
}

// insertBefore()
// Insert new element before cursor. Pre: length() > 0, index() >= 0.
void insertBefore(List L, int x){
	if (L == NULL){
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> index < 0){
		fprintf(stderr, "List Error: calling insertBefore not possible if cursor is undefined\n");
	}
	if (L -> cursor == L -> front){ // case where cursor is at front, null previous, adds N element to front.
		prepend(L, x);
	}else{
		Node N = newNode(x);
		N -> previous = L -> cursor -> previous; // sets N element's previous to cursor's previous.
		N -> next = L -> cursor; // sets N element's next to current cursor node.
		L -> cursor -> previous -> next = N; // need to point to the next element that used to be previous.
		L -> cursor -> previous = N; // need to point to a new previous element. Prevents memory errors.
		L -> index++; // increment index since new item added before cursor.
		L -> length++; // increment length of list since new item added.
	}
}

// insertAfter()
// Insert new element after cursor. Pre: length() > 0, index() >= 0.
void insertAfter(List L, int x){
	if (L == NULL){
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L -> index < 0){
		fprintf(stderr, "List Error: calling insertAfter not possible if cursor is undefined\n");
	}
	if (length(L) <= 0){
		fprintf(stderr, "List Error: calling insertAfter on an empty List\n");
	}
	if (L -> cursor == L -> back){ // case where cursor is at back, null next, adds N element to back.
		append(L, x);
	}else{
		Node N = newNode(x);
		N -> next = L -> cursor -> next; // sets N element's next to cursor's next node.
		N -> previous = L -> cursor; // sets N element's previous to current cursor node.
		L -> cursor -> next -> previous = N; // need to point to the previous element that used to be next.
		L -> cursor -> next = N; // need to point to a new next element. Prevents memory errors.
		L -> length++; // increment length of list since new item added. No need to increment index since item added after cursor.
	}
}

// deleteFront()
// Delete the front element. Pre: length() > 0.
void deleteFront(List L){
	Node N = NULL;
	if (L == NULL){
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
	}else{
		if (L -> length == 1){ // case where there is only one item in list so deleting item will create empty set.
			N = L -> front; // assign N node as front item.
			freeNode(&N); // free N to remove.
			L -> front = L -> back = NULL; // set front and back of list as NULL.
			L -> cursor = NULL; // set cursor to undefined.
			L -> index = -1; // set cursor index to undefined.
		}else{
			N = L -> front; // assign N node as front item.
			L -> front = L -> front -> next; // new front becomes old front's next node.
			L -> front -> previous = NULL; // assign new front's previous as NULL.
			if (L -> cursor != NULL){ // check that cursor does not become undefined.
				L -> index--; // if cursor is not undefined, decrement index since item is being removed.
			}
			freeNode(&N); // free N to remove.
		}
		L -> length--; // decrement length.
	}
}

// deleteBack()
// Delete the back element. Pre: length() > 0.
void deleteBack(List L){
	Node N = NULL;
	if (L == NULL){
		fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
	}else{
		if (L -> length == 1){ // case where there is only one item in list so deleting item will create empty set.
			N = L -> back; // assign N node as back item.
			freeNode(&N); // free N to remove.
			L -> back = L -> front = NULL; // set front and back nodes to NULL.
			L -> cursor = NULL; // set cursor to undefined.
			L -> index = -1; // set cursor index to undefined.
		}else{
			N = L -> back; // set N node to current back node.
			L -> back = N -> previous; // set new back node to be old back node's previous node.
			L -> back -> next = NULL; // sets new back node's next pointer to NULL.
			if (L -> index == L -> length - 1){ // checks if cursor is at back of list.
				L -> cursor = NULL;
				L -> index = -1; // sets cursor index to undefined.
			}
			freeNode(&N); // frees N to remove.
		}
		L -> length--; // decrements length.
	}
}

// delete()
// Delete cursor element, making cursor undefined. Pre: length() > 0, index() >= 0.
void delete(List L){
	if (L == NULL){
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0){
		fprintf(stderr, "List Error: calling delete() on empty List\n");
	}
	if (L -> index < 0){
		fprintf(stderr, "List error: calling delete() not possible if cursor is undefined\n");
	}
	if (L -> cursor == L -> front){ // case where cursor is at front.
		deleteFront(L);
	}
	else if (L -> cursor == L -> back){ // case where cursor is at back.
		deleteBack(L);
	}else{
		Node N = L -> cursor; // set N node to current cursor node.
		N -> previous -> next = N -> next; // set old cursor's previous ref to next.
		N -> next -> previous = N -> previous; // set old cursor's next ref to previous.
		L -> cursor = NULL;
		freeNode(&N); // free N node.	
		L -> index = -1; // sets cursor index to undefined.
		L -> length--; // decrement list length.
	}			
}

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of
// a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	Node N = NULL;
	if (L == NULL){
		fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	for (N = L -> front; N != NULL; N = N -> next){
		printf("%d ", N -> data);
	}
	printf("\n");
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L){
	Node N = NULL;
	List dup_list = newList(); // intiate a new list to copy to.
	if (length(L) > 0){
		N = L -> front; // sets N node to front item.
		while (N != NULL){
			append(dup_list, N -> data); // append data to new, dup list. Does not change current list.
			N = N -> next; // set N node to next item to be copied.
		}
	}
	dup_list -> cursor = NULL; // set copy list cursor to undefined.
	dup_list -> index = -1; // set copy list cursor index to undefined.
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
List concatList(List A, List B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "List Error: calling concatList on NULL list reference\n");
		exit(EXIT_FAILURE);
	}
	List C = newList();
	Node *current = A -> front;
	
	for (int i = 0; i < A -> length; i++){
		append(C, current -> value);
		current = current -> next;
	}
	
	current = B -> front;
	
	for (int i= 0, i < B -> length; i++){
		append (C, current -> value);
		current = current -> next;
	}
	return C;
}