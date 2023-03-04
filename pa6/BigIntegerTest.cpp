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
int main()
{
	BigInteger A;
	BigInteger B;
	BigInteger C;
	BigInteger D;
    string bar="1235679238312087451";
    BigInteger foo(bar);
    cout<<"original string: "<<bar<<endl;
    cout<<"Big int to string: "<<foo<<endl;
    string test = "-1231593872469213874982710412873487086087351024";
    BigInteger foo2(test);
    cout<<"original string: "<<test<<endl;
    cout<<"Big int to_string: "<<foo2<<endl;
    string test2="000000007";
    BigInteger BI(test2);
    cout<<"original string: "<<test2<<endl;
    cout<<"Big int to_string(): "<<BI<<endl;
    string test3=test2+test2;
    cout<<"original string: "<<test3<<endl;
    BigInteger BI2(test3);
    cout<<"Big int to_string(): "<<BI2<<endl;
    string test4="80000"+test3;
    cout<<"original string: "<<test4<<endl;
    BigInteger BI3(test4);
    cout<<"Big int to_string(): "<<BI3<<endl;
    string test5="12456sd903827";
    try{
        BigInteger BI4(test5);
    }catch(const invalid_argument& e){
        cout<<"Constructor correctly catches non-numeric in the middle"<<endl;
    }

    string test6 = "O00000077777777777777788888888889999999999999";
    try{
        BigInteger BI5(test6);
    }catch(const invalid_argument& e){
        cout<<"Construtor correctly catches non-numeric in front"<<endl;
    }    
    string test7= "000000000000000000000000008888888888888888888888887777777777777777a";
    try{
        BigInteger BI6(test7);
    }catch(const invalid_argument& e){
        cout<<"Constructor correctly catches non-numeric in rear"<<endl;
    }
    
    string compare1 = "123456789098764321";
    string compare2 = "999999992222222222";
    BigInteger BIc1(compare1);
    BigInteger BIc2(compare2);
    
    cout<<"BigInt 1: "<<BIc1<<endl;
    cout<<"BigInt 2: "<<BIc2<<endl;
	
	A = BigInteger("+111122223333");
    B = BigInteger("+222211110000");
	cout<<"A: "<<A<<endl;
    cout<<"B: "<<B<<endl;

    // pos + pos = pos
    D = BigInteger("+333333333333");
	C = A + B;
	//cout<<"C "<<C<<endl;

    A = BigInteger("+111122223333");
    B = BigInteger("-111122223333");
    A += B;
	cout<<"A: "<<A<<endl;
	cout<<"A sign: "<<A.sign()<<endl;
    if (A.sign() != 0)
      return 2;
}