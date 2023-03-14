//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa8
// WordFrequency.cpp
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
	size_t begin, end, len;
	ifstream in;
	ofstream out;
	string line;
	string word;
	//string delim = " "; 
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

	// check command line for correct number of arguments
	if( argc != 3 ){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
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

	// read each line of input file, then count and print words 
	Dictionary A;
	while (getline(in, line))  {
		len = line.length();
		// get first word
		begin = std::min(line.find_first_not_of(delim, 0), len);
		end   = std::min(line.find_first_of(delim, begin), len);
		word = line.substr(begin, end-begin);
		std::transform(word.begin(),word.end(),word.begin(),::tolower);
		while( word!="" ){  // we have a word
			if (A.contains(word)){
				valType& value = A.getValue(word);
				value++;
			}else{
				A.setValue(word, 1);
			}
         // get next word
			begin = std::min(line.find_first_not_of(delim, end+1), len);
			end   = std::min(line.find_first_of(delim, begin), len);
			word = line.substr(begin, end-begin);
			std::transform(word.begin(),word.end(),word.begin(),::tolower);

		}
	}
	out<<A<<endl;
   // close files 
	in.close();
	out.close();
}