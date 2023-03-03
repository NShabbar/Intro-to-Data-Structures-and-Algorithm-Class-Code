//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa6
// BigInteger.cpp
// implementation for BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include <stdexcept>
#include"List.h"
#include "BigInteger.h"
using namespace std;
// Global Variables --------------------------------------------------------
const int power = 9;
const long base = 1000000000;

// Private functions -------------------------------------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
	L.moveFront();
	for (int i = 0; i < L.length(); i++){
		int j = (L.moveNext() * -1);
		L.setBefore(j);
	}
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
	A.moveFront();
	B.moveFront();
	S.clear();
	while (A.position() < A.length() && B.position() < B.length()){
		int j = A.moveNext() + (B.moveNext()*sgn);
		S.insertBefore(j);
		S.moveNext();
	}
	while (A.position() < A.length()){
		int j = A.moveNext();
		S.insertBefore(j);
		S.moveNext();
	}
	while (B.position() < B.length()){
		int j = (B.moveNext()*sgn);
		S.insertBefore(j);
		S.moveNext();
	}
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L);

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	L.moveBack();
	for (int i = 0; i < p; i++){
		L.insertBefore(0);
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	L.moveFront();
	for (int i = 0; i < L.length(); i++){
		int j = L.moveNext() * m;
		L.setBefore(j);
	}
}


// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	List digits;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	if (s.length() == 0){
		throw invalid_argument("BigInteger: Constructor: empty string");
	}
	if (s[0] == '+' || s[0] == '-'){ // check for sign.
		if (s[0] == '+'){
			signum = 1;
		}
		else if (s[0] == '-'){
			signum = -1;
		}
		s.erase(s.begin());
	}else{ // if no sign then assumed positive.
		signum = 1;
	}
	if (s.length() == 0){
		throw invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	if (s[0] != '0'){ // get rid of leading zeros.
		s.erase(0, s.find_first_not_of('0'));
	}
	List digits;
	ListElement substring = 0;
	string temp = "";
	for (unsigned long int i = s.length(); i > 0; i--){
		if (!isdigit(s[i])){
			throw invalid_argument("BigInteger: Constructor: non-numeric string");
		}
		temp += s[i];
		if (temp.length() == power){
			substring = stol(temp);
			digits.insertAfter(substring);
			temp = "";
		}
	}
	substring = stol(temp);
	digits.insertAfter(substring);
}

// BigInteger()   
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	signum = 0;
	List digits;
	this -> signum = N.sign();
	this -> digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::BigInteger::sign() const{
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	List A = this -> digits;
	List B = N.digits;
	A.moveFront();
	B.moveFront();
	if (this -> sign() < N.sign()){
		return -1;
	}
	else if (this -> sign() > N.sign() ){
		return 1;
	}
	if (A.length() > B.length()){
		return 1;
	}
	else if (A.length() < B.length()){
		return -1;
	}
	while (A.position() < A.length()){
		ListElement num1 = A.moveNext();
		ListElement num2 = B.moveNext();
		if (num1 != num2){
			if (num1 > num2){
				return 1;
			}else{
				return -1;
			}
		}
	}
	return 0;
}
	


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	this -> digits.clear();
	signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
	if (sign() == 1){
		signum = -1;
	}
	else if (sign() == -1){
		signum = 1;
	}
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger add(const BigInteger& N) const;

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger sub(const BigInteger& N) const;

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger mult(const BigInteger& N) const;


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	string output = "";
	if (sign() == 0){
		output = '0';
		return output;
	}
	else if (sign() == -1){
		output += "-";
	}

	List dig = digits;
	dig.moveFront();
	while (dig.position() < dig.length()){
		ListElement num = dig.moveNext();
		string num_str = std::to_string(num);
		if (dig.position() > 1 && num_str.length() < power){
			for (int i = 0; i < (power - (int)num_str.length()); i++){
				output += '0';
			}
		}
		output += num_str;
	}
	return output;
}


// Overriden Operators -----------------------------------------------------
  
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	int eq = A.BigInteger::compare(B);
	if (eq == 0){
		return true;
	}else{
		return false;
	}
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	int eq = A.BigInteger::compare(B);
	if (eq == -1){
		return true;
	}else{
		return false;
	}
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	int eq = A.BigInteger::compare(B);
	if (eq == 0 || eq == -1){
		return true;
	}else{
		return false;
	}
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	int eq = A.BigInteger::compare(B);
	if (eq == 1){
		return true;
	}else{
		return false;
	}
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	int eq = A.BigInteger::compare(B);
	if (eq == 0 || eq == 1){
		return true;
	}else{
		return false;
	}
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}