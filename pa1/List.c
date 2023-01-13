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


	