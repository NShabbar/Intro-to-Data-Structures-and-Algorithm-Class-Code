//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa5
// Shuffle.cpp
// client use of List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
	List A;
	List B;
	D.moveFront();
	while (D.position() < (D.length()/2)){
		A.insertBefore(D.moveNext());
	}
	while (D.position() < D.length()){
		B.insertBefore(D.moveNext());
	}
	D.clear();
	A.moveFront();
	B.moveFront();
	while (A.position() != A.length() && B.position() != B.length()){
		D.insertBefore(B.moveNext());
		D.insertBefore(A.moveNext());
	}
	while (B.position() != B.length()){
		D.insertBefore(B.moveNext());
	}
}

int main(int argc, char* argv[]){
	if (argc !=2){
		cerr << "Usage: " << argv[0] << "incorrect value." << endl;
		return(EXIT_FAILURE);
	}
	int n = atoi(argv[1]);
	List D;
	cout << "deck size \t shuffle count" << endl;
	cout << "------------------------------" << endl;
	List C = List(D);
	
	for (int deck_count = 1; deck_count < n+1; deck_count++){
		int shuffle_count = 0;
		D.insertBefore(deck_count);	
		C = List(D);
		shuffle(D);
		shuffle_count++;
		while (!(C == D)){
			shuffle(D);
			shuffle_count++;
		}
		cout << " " << deck_count << "\t \t  " << shuffle_count << endl;
	}
}