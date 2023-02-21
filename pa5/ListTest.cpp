//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa5
// ListTest.cpp
// test for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

int main(int argc, char* argv[]){
	List A = new List();

	// insertAfter Test
	//-----------------------------------------------------------------------------	
	A.insertAfter(5);
	A.insertAfter(4);
	A.insertAfter(3);
	cout << "Printing list A: " << A.to_string;
	
	// insertBefore Test
	//-----------------------------------------------------------------------------	
	A.insertBefore(0);
	A.insertBefore(1);
	A.insertBefore(2);
	cout << "Printing list A: " << A.to_string;
	
	// length Test
	//-----------------------------------------------------------------------------	
	cout << "Printing length of list A: " << A.length();
	
	// front Test
	//-----------------------------------------------------------------------------	
	cout << "Printing front element of list A: " << A.front();
	
	// back Test
	//-----------------------------------------------------------------------------	
	cout << "Printing back element of list A: " << A.back();
	
	// position Test
	//-----------------------------------------------------------------------------	
	cout << "Printing cursor position of list A: " << A.position();
	
	// peekNext Test
	//-----------------------------------------------------------------------------	
	cout << "Printing element after cursor of list A: " << A.peekNext();
	
	// peekPrev Test
	//-----------------------------------------------------------------------------	
	A.moveNext();
	std::cout << "Printing element before cursor of list A: " << A.peekPrev();
	
	
	
}