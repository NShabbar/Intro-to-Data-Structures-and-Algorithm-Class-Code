//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa7
// DictionaryTest.cpp
// Test file for Dictionary.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;
int main(){
	Dictionary A;
	
    A.setValue("A", 6);
    A.setValue("B", 9);
    A.setValue("G", 11);
    A.setValue("V", 15);
    A.setValue("X", 13);
    A.setValue("Z", 100);
    std::string val = A.pre_string();
	
	cout<<val<<endl;
	
	cout<<"Testing pre_string(): "<<val<<endl;
	
	A.begin();
	cout<<"Testing begin(): "<<A.currentKey()<<endl;
	
	A.next();
	cout<<"Testing next(): "<<A.currentKey()<<endl;
	
	A.end();
	cout<<"Testing end(): "<<A.currentKey()<<endl;
	
	A.prev();
	cout<<"Testing prev(): "<<A.currentKey()<<endl;
	
	cout<<"Testing contains('B'): "<<A.contains("B")<<endl;
	
	cout<<"Testing size(): "<<A.size()<<endl;
	
	cout<<"Testing getValue('B'): "<< A.getValue("B")<<endl;
	
	cout<<"Testing hasCurrent(): "<<A.hasCurrent()<<endl;
	
	cout<<"Testing currentKey(): "<<A.currentKey()<<endl;
	
	cout<<"Testing currentVal(): "<<A.currentVal()<<endl;
	
	Dictionary B = A;
	
	cout<<"Testing equals(): "<<A.equals(B)<<endl;
	
	A.clear();
	cout<<"Testing clear(): "<<A<<endl;

}
