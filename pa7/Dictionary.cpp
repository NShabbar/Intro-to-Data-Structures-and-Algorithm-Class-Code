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
	s = "key: ";
	if (R != nil){
		inOrderString(R.left);
		cout<<R.key<<endl;
		inOrderString(R.right);
	}	//not finished.
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void preOrderString(std::string& s, Node* R) const{
	if (R != nil){
		cout<<R.key<<endl;
		preOrderString(R.left);
		preOrderString(R.right);
	}	//not finished.
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void preOrderCopy(Node* R, Node* N){
	if (R != nil){
		N.key = R.key;
	}	//not finished.
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void postOrderDelete(Node* R){
	if (R != nil){
		postOrderDelete(R.left);
		postOrderDelete(R.right);
		delete(R.key);
	}	//not finished.
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Node* search(Node* R, keyType k) const{
	if (R == nil || k == R.key){
		return R;
	}
	else if (k < R.key){
		return search(R.left, k);
	}else{
		return search(R.right, k);
	}	//not finished.
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Node* findMin(Node* R){
	if (R != nil){
		while (R.left != nil){
			R = R.left;	
		}
		return R;
	}	//not finished.
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Node* findMax(Node* R){
	if (R != nil){
		while (R.right != nil){
			R = R.right;
		}
		return R;
	}	//not finished.
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Node* findNext(Node* N){
	if (N.right != nil){
		return findMin(N.right);
	}
	Node y = N.parent;
	while (y != nil && N == y.right){
		N = y;
		y = y.parent;
	}
	return y;	//not finished.
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Node* findPrev(Node* N){
	if (N.left != nil){
		return findMax(N.left);
	}
	Node y = N.parent;
	while (y != nil && N == y.left){
		N = y;
		y = y.parent;
	}
	return y;	//not finished.
}
   
   
// Class Constructors & Destructors ----------------------------------------
Dictionary::Node(keyType k, valType v){
	key = k;
	val = v;
	parent -> nil;
	left -> nil;
	right -> nil;
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
	
	Node* N = D.key;
	for (int i = 0; i != D.size(); i++){
		this -> setValue(D.key, D.val);
		D.next();
	}	//not finished.
}

// Destructor
Dictionary::~Dictionary();


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
	begin();
	for (int i = 0; i != size(); i++){
		if (this -> key == k){
			return true;
		}
		next();
	}
	return false; //not finished.
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	begin();
	for (int i = 0; i != size(); i++){
		if (this -> key == k){
			return this -> val;
		}
		next();
	}
	throw std:: length_error("Dictionary: getValue(): k does not exist.");
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const;

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const;

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const;


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear();

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v);

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k);

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	if (size() == 0){
		throw std:: length_error("Dictionary: begin(): empty dictionary.");
	} //not finished.
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	if (size() == 0){
		throw std:: length_error("Dictionary: end(): empty dictionary.");
	} //not finished.
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next();

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev();


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const;

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const;

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	bool eq = false;
	Node* N = this -> key -> left;
	Node* M = D.key -> left;
	
	eq = (this -> size() == D.size());
	
	while (eq && N != nil){
		eq = (N -> val == M -> val);
		N = N.next();
		M = M.next();
	}
	return eq;
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