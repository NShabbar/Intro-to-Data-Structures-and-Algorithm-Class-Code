//-----------------------------------------------------------------------------
// ListTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
	int i;
	List A = newList();
	// List B = newList();
	
	
	// Prepend Test
	//-----------------------------------------------------------------------------
	printf("Testing prepend() function of List.c\n");
	
	for (i = 10; i >= 1; i--){
		prepend(A, i);
		// prepend(B, i);
	}
	
	printf("Printing List A: ");
	printList(stdout, A);
	printf("\n");
	// printf("Printing List B: ");
	// printList(B);
	// printf("\n");
	
	
	// Append Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing append() function of List.c\n");
	
	for (i = 11; i <= 15; i++){
		append(A, i);
		// append(B, i);
	}
	
	printf("Printing List A: ");
	printList(stdout, A);
	printf("\n");
	// printf("Printing List B: ");
	// printList(B);
	// printf("\n");
	
	
	// Copy List Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing copyList() function of List.c\n");
	List B = copyList(A);
	printList(stdout, B);
	
	
	// Equals Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing equals() function of List.c\n");
	equals(A, B);
	printf("%s", equals(A,B)?"true":"false");
	
	
	// Length Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing length() function of List.c\n");
	printf("Printing length of List A: ");
	printf("%d", length(A));
	
	
	// Index, get, and Cursor Movement Tests
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing index(), moveFront, moveBack, movePrev, moveNext and get functions of List.c\n");
	printf("Printing index of List A before any movement: ");
	printf("%d", index(A));
	
	printf("\n");
	printf("Printing index of List A at the front of the list: ");
	moveFront(A);
	printf("%d", index(A));
	printf("\nGetting value of index: %d", get(A));
	
	printf("\n");
	printf("Printing index of List A at the back of the list: ");
	moveBack(A);
	printf("%d", index(A));
	printf("\nGetting value of index: %d", get(A));
	
	printf("\n");
	printf("Printing index of List A at the previous index of the list: ");
	movePrev(A);
	printf("%d", index(A));
	printf("\nGetting value of index: %d", get(A));
	
	printf("\n");
	printf("Printing index of List A at the next index of the list: ");
	moveNext(A);
	printf("%d", index(A));
	printf("\nGetting value of index: %d", get(A));
	
	printf("\n");
	printf("Printing index of List A at undefined of the list: ");
	moveFront(A);
	movePrev(A);
	printf("%d\n", index(A));
	
	// Front Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing front() function of List.c in List A\n");
	printf("Printing front element of List A: %d", front(A));
	
	// Back Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing back() function of List.c in List A\n");
	printf("Printing back element of List A: %d", back(A));
	
	// Set Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing set() function of List.c by changing first element to 0 in List A\n");
	moveFront(A);
	set(A, 0);
	printList(stdout, A);
	printf("\n");
}