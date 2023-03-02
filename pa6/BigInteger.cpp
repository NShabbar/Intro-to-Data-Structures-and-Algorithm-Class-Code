//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa6
// BigInteger.cpp
// implementation for BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
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
		j = L.setBefore(j);
	}
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
	A.moveFront();
	B.moveFront();
	S.clear();
	for (int i = 0; i < A.length(); i++){
		int j = A.moveNext() + (B.moveNext()*sgn);
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
void shiftList(List& L, int p);

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	L.moveFront();
	for (int i = 0; i < L.length(); i++){
		int j = L.moveNext() * m;
		L.setBefore(j);
	}
}

// removes undesired characters.
std::string CleanList(std::string str){
	string output = "";
	for (unsigned long int i = 0; i < str.length(); i++){
		if ( str[i] != '(' && str[i] != ')' && str[i] != ','){
			out += str[i];
		}
	}
	return output;
}

// returns any potential lost zeros.
std::string LostZeros(std::string str){
	string output = "";
	string number = "";
	string temp = "";
	while (unsigned long int i = 0 < str.length()){
		if (str[i] == ' '){
			if (number.length() < power){
				while (temp.length() != power{
					temp.insert(temp.begin(), '0');
				}
			}
			number += temp;
			temp = "";
		}else{
			temp.insertBefore(str[i]);
		}
		i++;
		output += nnumber;
		number = "";
	}
	while (temp.length() ! = power){
		temp.insert(temp.begin(), '0');
	}
	output += temp;
	return output;
}


// goes through string to determine if string is a number.
bool Numbers(std::string str){
	for (unsigned long int i = 0; i < str.length(); i++){
		if (isdigit(str[i]) == false){
			return false;
		}
	}
	return true;
}

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	if (s.empty()){
		throw cerr << "BigInteger: Constructor: empty string" << endl;
	}
	if (s[0] == '+' || s[0] == '-'){ // check for sign.
		if (s[0] == '+'){
			signum = 1;
		}
		else if (s[0] == '-'){
			signum = -1;
		}
		s.erase(s.begin());
	}
	else if (s[0] == '0'){ // if sign is zero, empty list.
		signum = 0;
		digits = List();
		return;
	}else{ // if no sign then assumed positive.
		signum = 1;
	}
	if (s != '0'){ // get rid of leading zeros.
		s.erase(0, s.find_first_not_of('0'));
	}
	digits = List();
	while ((s.length() % power) != 0){
		s = s.insert(0, '0');
	}
	int beginning = 0;
	int end = s.length() - 1;
	for (unsigned long int i = 0; i < (s.length() / power); i++){
		beginning = end - (power -1);
		string substring = s.substr(beginning, power);
		if (!Numbers(substring)){
			throw cerr << "BigInteger: Constructor: non-numeric string" << endl;
		}else{
			digits.moveFront();
			digits.insertAfter(stol(substring));
		}
		end = beginning - 1;
	}
}

// BigInteger()   
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	signum = 0;
	digits = List();
	this -> signum = N.sign();
	this -> digits = N -> digits;
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
	if (A-> digits.equals(B -> digits)){
		return 0;
	}
	if (A.sign() < B.sign()){
		return -1;
	}
	if (A.sign() > B.sign() ){
		return 1;
	}
}
	


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	BigInteger C;
	this -> digits = C.digits;
	signum = C.sign();
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
	string str_list = digits.to_string();
	str_list = CleanList(str_list);
	str_list = LostZeros(str_list);
	if (str_list != '0'){
		str_list.erase(0, str_list.find_first_not_of('0'));
	}
	output += str_list;
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
	bool eq = A.BigInteger::compare(B);
	if (eq == 0){
		return true;
	}else{
		return false;
	}
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	bool eq = A.BigInteger::compare(B);
	if (eq == -1){
		return true;
	}else{
		return false;
	}
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	bool eq = A.BigInteger::compare(B);
	if (eq == 0 || eq == -1){
		return true;
	}else{
		return false;
	}
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	bool eq = A.BigInteger::compare(B);
	if (eq == 1){
		return true;
	}else{
		return false;
	}
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	bool eq = A.BigInteger::compare(B);
	if (eq == 0 || eq == 1){
		return true;
	}else{
		return false;
	}
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	if (A.sign() == 0){
		return B;
	}
	else if (B.sign() == 0){
		return A;
	}else{
		BigInteger C = A.add(B);
		return C;
	}
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	BigInteger C = A.add(B);
	A.digits = C.digits;
	C -> signum = C.sign();
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	if (A.sign() == 0){
		B.sign() = 1; // B.negateList();
		return B;
	}
	else if (B.sign() == 0){
		return A;
	}
	else if (A == B){
		BigInteger C;
		return C;
	}else{
		BigInteger C = A.sub(B);
		return C;
	}
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	BigInteger C = A.sub(B);
	A.digits = C.digits;
	C -> signum = C.sign();
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	if (A.sign() == 0 || B.sign() == 0){
		BigInteger C;
		return C;
	}else{
		BigInteger C = A.mult(B);
		if (A.sign() == B.sign()){
			C -> signum = 1;
		}else{
			C -> signum = -1;
		}
		return C;
	}
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	BigInteger C = A.mult(B);
	A.digits = C.digits;
	A -> signum = C.sign();
	return A;
}