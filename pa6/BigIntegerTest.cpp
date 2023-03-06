//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa6
// BigIntegerTest.cpp
// Test Client For BigInteger ADT
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include <iostream>
#include <string>
#include "List.h"
using namespace std;
int main(){
	
	cout<<"Testing BigInteger String Conversion, no sign: "<<endl<<endl;
    string str1="1111111111222222223333333";
    BigInteger A(str1);
    cout<<"String: "<<str1<<endl;
    cout<<"BigInteger(string): "<<A<<endl;
	
	cout<<"Testing BigInteger String Conversion, negative sign: "<<endl<<endl;
    string str2 = "-1111111111222222223333333";
    BigInteger B(str2);
    cout<<"String: "<<str2<<endl;
    cout<<"BigInteger(string): "<<B<<endl;
	
	cout<<"Testing BigInteger String Conversion, leading zeros: "<<endl<<endl;
    string str3 ="000000000000000012312310";
    BigInteger C(str3);
    cout<<"String: "<<str3<<endl;
    cout<<"BigInteger(string): "<<C<<endl;
	
	cout<<"Testing add, pos. and neg.: "<<endl<<endl;
	cout<<"A: "<<A<<endl;
	cout<<"B: "<<B<<endl;
    BigInteger D = A+B;
    cout<<"D = A+B: "<<D<<endl;
	
	cout<<"Testing add, pos. and pos. with many zeros: "<<endl<<endl;
	BigInteger A1("0000000100000");
	BigInteger B1("1000000000001");
	cout<<"A: "<<A<<endl;
	cout<<"B: "<<B<<endl;
    BigInteger D1 = A1+B1;
    cout<<"D = A+B: "<<D<<endl;
	
	cout<<"Testing add, pos. and pos. with different lengths: "<<endl<<endl;
	BigInteger A2("0000000100000");
	BigInteger B2("1000000000001000");
	cout<<"A: "<<A<<endl;
	cout<<"B: "<<B<<endl;
    BigInteger D2 = A2+B2;
    cout<<"D = A+B: "<<D<<endl;
	
	cout<<"Testing sub, pos. and pos.: "<<endl<<endl;
	cout<<"A: "<<A<<endl;
	cout<<"B: "<<B<<endl;
    D = A-B;
    cout<<"D = A-B: "<<D<<endl;
	
	cout<<"Testing sub, pos. and neg.: "<<endl<<endl;
	cout<<"A: "<<A<<endl;
	cout<<"B: "<<B<<endl;
    D = A-B;
    cout<<"D = A-B: "<<D<<endl;
	
	cout<<"Testing mult, pos. and neg.: "<<endl<<endl;
	cout<<"A: "<<A<<endl;
	cout<<"B: "<<B<<endl;
    D = A-B;
    cout<<"D = A-B: "<<D<<endl;

	cout<<"Testing mult, pos. and pos.: "<<endl<<endl;
	cout<<"A: "<<A2<<endl;
	cout<<"B: "<<B2<<endl;
    D = A2-B2;
    cout<<"D = A-B: "<<D<<endl;
}