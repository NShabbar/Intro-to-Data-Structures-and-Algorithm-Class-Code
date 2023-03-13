//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa8
// Order.cpp
// Top Level
//-----------------------------------------------------------------------------
#include <algorithm> 
#include<iostream>
#include<string>
#include <stdexcept>
#include"Dictionary.h"
#include<iostream>
#include<fstream>
using namespace std;
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
   string str1;
   Dictionary A;
   
   int line_count = 0;
   while (getline(in, str1)){
	   line_count++;
	   A.setValue(str1, line_count);
   }
   out<<A<<endl;
   out<<A.pre_string()<<endl;
   in.close();
   out.close();
}