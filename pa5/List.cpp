//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa5
// List.cpp
// implementation for List ADT
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
	pos_cursor = 0;
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
	pos_cursor = 0;
	num_elements = 0;
	
	// load elements of L into this List.
	Node* N = L.frontDummy -> next;
	while (N != L.backDummy){
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
	if (length() == 0){
		throw std:: length_error("List: front(): empty List");
	}
	return frontDummy -> next -> data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if (length() == 0){
		throw std:: length_error("List: back(): empty List");
	}
	return backDummy -> prev -> data;
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
	if (position() > length()){
		throw std:: length_error("List: peekNext(): back of List");
	}
	return afterCursor -> data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if (position() < 0){
		throw std:: length_error("List: peekprev(): front of List");
	}
	return beforeCursor -> data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	moveFront();
	while (length() > 0){
		eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy -> next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy -> prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if (position() == length()){
		throw std:: length_error("List: moveNext(): end of List");
	}
	ListElement N_data = afterCursor -> data;
	pos_cursor++;
	beforeCursor = afterCursor;
	afterCursor = afterCursor -> next;
	return N_data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if (position() == 0){
		throw std:: length_error("List: movePrev(): front of List");
	}
	ListElement N_data = beforeCursor -> data;
	pos_cursor--;
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor -> prev;
	return N_data;
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
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* temp = new Node(x);
	beforeCursor -> next = temp;
	temp -> prev = beforeCursor;
	afterCursor -> prev = temp;
	temp -> next = afterCursor;
	beforeCursor = temp;
	pos_cursor++;
	num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if (position() == length()){
		throw std:: length_error("List: setAfter(): end of List");
	}
	afterCursor -> data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if (position() == 0){
		throw std:: length_error("List: setBefore(): front of List");
	}
	beforeCursor -> data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if (position() == length()){
		throw std:: length_error("List: eraseAfter(): end of List");
	}
	Node* N = afterCursor;
	Node* M = afterCursor -> next;
	beforeCursor -> next = M;
	M -> prev = beforeCursor;
	afterCursor = M;
	delete(N);
	num_elements--;
	
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if (position() == 0){
		throw std:: length_error("List: eraseBefore(): front of List");
	}
	Node* N = beforeCursor;
	Node* M = beforeCursor -> prev;
	M -> next = afterCursor;
	afterCursor -> prev = M;
	delete(N);
	beforeCursor = M;
	pos_cursor--;
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
	while (afterCursor != backDummy){
		if (moveNext() == x){
			return position();
		}
	}
	return -1;
}					

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while (beforeCursor != frontDummy){
		if (movePrev() == x){
			return position();
		}
	}
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	Node* N;
	Node* M;
	int count_N = 0;
	int count_M = 0;
	int flag = 0;
	for (N = frontDummy -> next; N -> next != backDummy && N != backDummy; N = N -> next){
		count_M = 1;
		for (M = N -> next; M != backDummy; M = M -> next){
			while (M -> data == N -> data){
				Node* L = M -> next;
				if (count_N + count_M < pos_cursor){
					pos_cursor--;
				}
				M -> prev -> next = L;
				L -> prev = M -> prev;
				if (M == beforeCursor){
					beforeCursor = L -> prev;
				}
				else if (M == afterCursor){
					afterCursor = L;
				}
				delete(M);
				M = L;
				num_elements--;
				if (L == backDummy){
					flag = 1;
					break;
				}
			}
			count_M++;
			if (flag == 1){
				flag = 0;
				break;
			}
		}
		count_N++;
	}
}
						
		
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List conc;
	Node* N = this ->  frontDummy;
	Node* M = L.frontDummy;
	while (N -> next != this -> backDummy){
		// cons.moveBack(); This may be necessary?
		conc.insertBefore(N -> next -> data);
		N = N -> next;
	}
	while (M -> next != L.backDummy){
		// cons.moveBack();
		conc.insertBefore(M -> next -> data);
		M = M -> next;
	}
	conc.moveFront();
	return conc;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	Node* N = nullptr;
	std::string s = "(";
	
	for (N = frontDummy; N != backDummy; N = N -> next){
		if (N==frontDummy || N == backDummy){
			continue;
		}
		s += std:: to_string(N -> data)+", ";
	}
	s+= "\b\b)";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = this -> frontDummy -> next;
	Node* M = R.frontDummy -> next;
	
	eq = (this -> length() == R.length());

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
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
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
		std::swap(num_elements, temp.num_elements);
	}
	// return this with the new data.
	return *this;
	//the copy, if there is one, is deleted upon return.
}