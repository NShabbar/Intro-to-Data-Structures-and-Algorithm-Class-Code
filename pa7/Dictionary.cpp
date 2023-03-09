 //-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa7
// Dictionary.cpp
// Implementation for Dictionary ADT
//-----------------------------------------------------------------------------  
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;
// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void inOrderString(std::string& s, Node* R) const{
	if (R != nil){
		inOrderString(s, R -> left);
		s += R -> key;
		s += " : ";
		s += R -> val;
		s += '\n';
		inOrderString(s, R -> right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void preOrderString(std::string& s, Node* R) const{
	if (R != nil){
		s += R -> key;
		s += " : ";
		s += R -> val;
		s += '\n';
		preOrderString(R -> left);
		preOrderString(R -> right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void preOrderCopy(Node* R, Node* N){
	Node* copy;
	if (R == N){
		return;
	}
	if (R != nil){
		setValue(R -> key, R -> val);
		preOrderCopy(R -> left, N);
		preOrderCopy(R -> right, N);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void postOrderDelete(Node* R){
	if (R != nil){
		postOrderDelete(R -> left);
		postOrderDelete(R -> right);
		delete(R -> key);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Node* search(Node* R, keyType k) const{
	if (R == nil || k == R.key){
		return R;
	}
	else if (k < R -> key){
		return search(R -> left, k);
	}else{
		return search(R -> right, k);
	}
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Node* findMin(Node* R){
	if (R != nil){
		while (R -> left != nil){
			R = R -> left;	
		}
		return R;
	}
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Node* findMax(Node* R){
	if (R != nil){
		while (R -> right != nil){
			R = R -> right;
		}
		return R;
	}
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Node* findNext(Node* N){
	if (N -> right != nil){
		return findMin(N -> right);
	}
	Node y = N -> parent;
	while (y != nil && N == y -> right){
		N = y;
		y = y -> parent;
	}
	return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Node* findPrev(Node* N){
	if (N -> left != nil){
		return findMax(N -> left);
	}
	Node y = N -> parent;
	while (y != nil && N == y -> left){
		N = y;
		y = y -> parent;
	}
	return y;
}
	
}

void Dictionary::Transplant(Node* U, Node* V){
	if (U -> parent == nil){
		D -> root = V;
	}
	else if (U == U -> parent -> left){
		U -> parent -> left = V;
	}else{
		U -> parent -> right = V;
	}
	if (V != nil){
		V -> parent = U -> parent);
	}
}
   
   
// Class Constructors & Destructors ----------------------------------------
Dictionary::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	nil = newNode("nil", 0);
	nil -> left = nil;
	nil -> right = nil;
	current = nil;
	root = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	nil = newNode("nil", 0);
	nil -> left = nil;
	nil -> right = nil;
	current = nil;
	root = nil;
	num_pairs = 0;
	
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
	clear();
	delete(nil);
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
	if (search(root, k) != nil){
		return true;
	}
	return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	Node* value = search(root, k);
	if (value != nil){
		return  value -> val;
	}
	throw std:: logic_error("Dictionary: getValue(): k does not exist.");
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
	if (current != nil){
		return true;
	}
	return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
	if (!hasCurrent){
		throw std:: logic_error("Dictionary: currentKey(): k does not exist.");
	}
	return current -> key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if (!hasCurrent){
		throw std:: logic_error("Dictionary: currentKey(): k does not exist.");
	}
	return current -> val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	postOrderDelete(root);
	current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node* y = nil;
	Node* R = root;
	Node* N = new Node(k, v);
	while (R != nil){
		y = R;
		if (R -> key == k){
			R -> value = v;
			delete(N);
			return;
		}
		if (N -> key < R -> key){
			R = R -> left;
		}else{
			R = R -> right;
		}
	N -> parent = y;
	num_pairs++;
	if (y == nil){
		R = N;
	}
	else if (N -> key < y -> key){
		y -> left = N;
	}else{
		y -> right = N;
	}
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
	if (!contains(k)){
		throw std:: logic_error("Dictionary: remove(): k not contained in Dictionary.");
	}
	Node* del = search(root, k);
	if (del -> left == nil){
		Transplant(del, del -> right);
	}
	else if (del -> right == nil){
		Transplant(del, del -> left);
	}else{
		Node* min = findMin(del -> right);
		if (min -> parent != del){
			Transplant(min, min -> right);
			min -> right = del -> right;
			min -> right -> parent = min;
		}
		Transplant(del, min);
		mi -> left = del -> left;
		min -> left -> parent = min;
	}
	if (del == current){
		current = nil;
	}
	delete(del);
	num_pairs--;
}
	

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	current = root;
	while (current ->left != nil){
		current = current -> left;
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	current = root;
	while (current -> right != nil){
		current = current -> right;
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	(!hasCurrent){
		throw std:: logic_error("Dictionary: next(): has no current.");
	}
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	(!hasCurrent){
		throw std:: logic_error("Dictionary: prev(): has no current.");
	}
	current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	string s = "";
	inOrderString(s, root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	string s = "";
	preOrderString(s, root);
	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	if (this -> size() != D.size()){
		return false;
	}
	string str1 == "";
	string str2 == "";
	this.inOrderString(str1, this -> root);
	D.inOrderString(str2, D.root);
}


// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& operator=( const Dictionary& D ){
	if (this != &D){
		Dictionary temp = D;
		
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this; //not finished.
}