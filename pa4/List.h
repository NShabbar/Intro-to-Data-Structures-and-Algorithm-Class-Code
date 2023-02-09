//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa4
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>

// Exported types -------------------------------------------------------------
typedef void* ListElement;
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
void* front(List L);

// back()
// Returns front element of L. Pre: length() > 0
void* back(List L);

// get()
// Returns cursor element of L. Pre: length() > 0, index() >= 0
void* get(List L);

/* // isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);
 */

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element's data with x. Pre: length() > 0, index() >= 0.
void set(List L, ListElement x);

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
void prepend(List L, ListElement x);

// append()
// Insert new element into L. If L is non-empty, insertion takes place after the back element.
void append(List L, ListElement x);

// insertBefore()
// Insert new element before cursor. Pre: length() > 0, index() >= 0.
void insertBefore(List L, ListElement x);

// insertAfter()
// Insert new element after cursor. Pre: length() > 0, index() >= 0.
void insertAfter(List L, ListElement x);

// deleteFront()
// Delete the front element. Pre: length() > 0.
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length() > 0.
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. Pre: length() > 0, index() >= 0.
void delete(List L);


// Extra Credit operation ------------------------------------------------------

//concatList()
// Returns a new List which is the concatenation of A and B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);

#endif