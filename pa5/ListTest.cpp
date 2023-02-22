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
using namespace std;
int main(){
	List A;
	cout << "Printing length of list A: " << A.length() << endl;

	// insertAfter Test
	//-----------------------------------------------------------------------------	
	A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);
	A.insertAfter(5);
	A.insertAfter(4);
	A.insertAfter(3);
	cout << "Printing list A: " << A << endl;
	
	// insertBefore Test
	//-----------------------------------------------------------------------------	
	A.insertBefore(0);
	A.insertBefore(1);
	A.insertBefore(2);
	cout << "Printing list A: " << A << endl;
	
	// length Test
	//-----------------------------------------------------------------------------	
	cout << "Printing length of list A: " << A.length() << endl;
	
	// front Test
	//-----------------------------------------------------------------------------	
	cout << "Printing front element of list A: " << A.front() << endl;
	
	// back Test
	//-----------------------------------------------------------------------------	
	cout << "Printing back element of list A: " << A.back() << endl;
	
	// position Test
	//-----------------------------------------------------------------------------	
	cout << "Printing cursor position of list A: " << A.position() << endl;
	
	// peekNext Test
	//-----------------------------------------------------------------------------	
	cout << "Printing element after cursor of list A: " << A.peekNext() << endl;
	
	// peekPrev Test
	//-----------------------------------------------------------------------------	
	cout << "Printing element before cursor of list A: " << A.peekPrev() << endl;
	
	// eraseAfter Test
	//-----------------------------------------------------------------------------	
	for (int i = 0; i < A.length()+1; i++){
		cout << "Printing element being deleted of list A: " << A.peekNext() << endl;
		A.eraseAfter();
	}

}