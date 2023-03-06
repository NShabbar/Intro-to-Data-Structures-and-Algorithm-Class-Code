//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa6
// Arithmetic.cpp
// Top Level
//-----------------------------------------------------------------------------
#include <algorithm> 
#include<iostream>
#include<string>
#include <stdexcept>
#include"List.h"
#include "BigInteger.h"
#include<iostream>
#include<fstream>
using namespace std;
BigInteger Exponent(BigInteger A, int e){
	BigInteger res;
	while (e != 0) {
        res = res * A;
        --e;
    }
	return res;
}

int main(int argc, char* argv[]){
	ifstream in;
	ofstream out;
	if (argc !=3){
		cerr << "Usage: " << argv[0] << "incorrect value." << endl;
		return(EXIT_FAILURE);
	}
	 // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }
   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   string value1;
   string value2;
   string blank;
   
   getline(in, value1);
   getline(in, blank);
   getline(in, value2);
   
   BigInteger A(value1);
   BigInteger B(value2);
   
   out<<A<<endl<<endl;
   out<<B<<endl<<endl;
   
   BigInteger C;
   C = A + B;
   out<<C<<endl<<endl;
   
   C = A - B;
   out<<C<<endl<<endl;
   
   C = A - A;
   out<<C<<endl<<endl;
   
   BigInteger three("3");
   BigInteger two("2");
   C = (three*A) - (two*B);
   out<<C<<endl<<endl;
   
   C = A * B;
   out<<C<<endl<<endl;
   
   C = Exponent(A, 2);
   out<<C<<endl<<endl;
   
   C = Exponent(B, 2);
   out<<C<<endl<<endl;
   
   BigInteger nine("9");
   BigInteger sixT("16");
   C = (nine*Exponent(A, 4)) + (sixT*Exponent(B, 5));
   out<<C<<endl<<endl;
}