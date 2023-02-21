//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}	
// Class Constructors & Destructors ----------------------------------------
   
// Creates new List in the empty state.
List::List(){
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy -> next = backDummy;
	backDummy -> prev = frontDummy;
	
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0; // this should maybe be 1?
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
	// make this an empty List.
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy -> next = backDummy;
	backDummy -> prev = frontDummy;
	
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0; // this should maybe be 1?
	num_elements = 0;
	
	// load elements of L into this List.
	Node* N = L.frontDummy;
	while (N != nullptr){
		this -> insertBefore(N -> data);
		N = N -> next;
	}
}

// Destructor
List::~List(){
	this -> clear();
	delete(frontDummy);
	delete(backDummy);
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if (num_elements == 0){
		throw std:: length_error("List: front(): empty List");
	}
	return frontDummy -> next;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if (num_elements == 0){
		throw std:: length_error("List: back(): empty List");
	}
	return backDummy -> prev;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if (pos_cursor == num_elements){
		throw std:: length_error("List: peekNext(): empty List");
	}
	return afterCursor;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if (pos_cursor <= 0){
		throw std:: length_error("List: peekprev(): empty List");
	}
	return beforeCursor;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	if (length() == 0){
		throw std:: length_error("List: clear(): empty List");
	}
	moveBack();
	while (num_elements != 0){
		eraseBefore();
		num_elements--; // this and pos should be done in erase
		pos_cursor--;
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	if (length() > 0){
		Node* N = frontDummy -> next;
		pos_cursor = 0;
	}
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	if (length() > 0){
		Node* N = backDummy -> prev;
		pos_cursor = length();
	}
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if (pos_cursor == length()){
		throw std:: length_error("List: moveNext(): end of List");
	}
	Node* N = afterCursor;
	beforeCursor = afterCursor;
	afterCursor = afterCursor -> next;
	pos_cursor++;
	return N -> data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if (pos_cursor == 0){
		throw std:: length_error("List: movePrev(): front of List");
	}
	Node* N = beforeCursor;
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor -> prev;
	pos_cursor--;
	return N -> data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* temp = new Node(x);
	afterCursor -> prev = temp;
	temp -> next = afterCursor;
	beforeCursor -> next = temp;
	temp -> prev = beforeCursor;
	afterCursor = temp;
	this -> num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* temp = new Node(x);
	beforeCursor -> next = temp;
	temp -> prev = beforeCursor;
	afterCursor -> prev = temp;
	temp -> next = afterCursor;
	this -> beforeCursor = temp;
	this -> num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if (pos_cursor == length()){
		throw std:: length_error("List: setAfter(): end of List");
	}
	afterCursor -> data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if (pos_cursor == 0){
		throw std:: length_error("List: setBefore(): front of List");
	}
	beforeCursor -> data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if (pos_cursor == length()){
		throw std:: length_error("List: eraseAfter(): end of List");
	}
	Node* N = afterCursor;
	beforeCursor -> next = afterCursor -> next;
	afterCursor -> next -> prev = beforeCursor;
	delete(N);
	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if (pos_cursor == 0){
		throw std:: length_error("List: eraseBefore(): front of List");
	}
	Node* N = beforeCursor;
	afterCursor -> prev = beforeCursor -> prev;
	beforeCursor -> prev -> next = afterCursor;
	delete(N);
	num_elements--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	while (pos_cursor != length()){
		if (afteCursor -> data == x){
			return pos_cursor;
		}
		moveNext();
	}
	if (pos_cursor == length()){
		return -1
	}
}					

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while (pos_cursor != 0){
		if (beforeCursor -> data == x){
			return pos_cursor;
		}
		movePrev();
	}
	if (pos_cursor == 0){
		return -1;
	}
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup();
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List conc;
	Node* N = this ->  frontDummy;
	Node* M = L.frontDummy;
	while (N != nullptr){
		// cons.moveBack(); This may be necessary?
		conc.insertBefore(N -> data);
		N = N -> next;
	}
	while (M != nullptr){
		// cons.moveBack();
		conc.insertBefore(M -> data);
		M = M -> next;
	}
	return conc;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string to_string() const{
	Node* N = nullptr;
	std::string s = "";
	
	for (N = frontDummy; N != nullptr; N = N -> next){
		s += std:: to_string(N -> data)+" ";
	}
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;
	
	eq = (this -> num_elements == R.num_elements);
	N = this -> frontDummy;
	M = R.frontDummy;
	while( eq && N != nullptr){
		eq = (N -> data == M -> data);
		N = N -> next;
		M = M -> next;
	}
	return eq;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
friend std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
friend bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if (this != &L){ // not self assignment.
		// make a copy of L.
		List temp = L;
		
		// then swap the copy's fields with fields of this.
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_ursor);
		std::swap(num_elements, temp.num_elements);
	}
	// return this with the new data.
	return *this;
	//the copy, if there is one, is deleted upon return.
}