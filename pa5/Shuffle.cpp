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

void shuffle(List& D){
	List A;
	List B;
	for (D.moveFront(); D.position() < (D.length()/2); D.moveNext()){
		A.insertBefore(D.moveNext());
	}
	for (D.position(); D.position() < D.length(); D.moveNext()){
		B.insertBefore(D.moveNext());
	}
	D.clear();
	A.moveFront();
	B.moveFront();
	while (A.position() >= 0 && B.position() >= 0){
		D.insertAfter(B.moveNext());
		D.insertAfter(A.moveNext());
	}
	while (A.position() >= 0){
		D.insertAfter(A.moveNext());
	}
	while (B.position() >= 0){
		D.insertAfter(A.moveNext());
	}
}

int main(int n){
	List D;
	for (int i = 0; i < n; i++){
		D.insertBefore(i);
	}
	List C = List(D);
	C.shuffle(D);	
}