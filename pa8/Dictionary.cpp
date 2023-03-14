 //-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa8
// Dictionary.cpp
// Implementation for Dictionary ADT
//-----------------------------------------------------------------------------  
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

#define BLK 1
#define RED 2

using namespace std;
// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if (R != nil){
		inOrderString(s, R -> left);
		s += R -> key;
		s += " : ";
		s += std::to_string(R -> val);
		s += '\n';
		inOrderString(s, R -> right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if (R != nil){
		s += R -> key;
		s += '\n';
		preOrderString(s, R -> left);
		preOrderString(s, R -> right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
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
void Dictionary::postOrderDelete(Node* R){
	if (R != nil){
		postOrderDelete(R -> left);
		postOrderDelete(R -> right);
		if (R == R -> parent -> left){
			R -> parent -> left = nil;
		}
		else if (R == R -> parent -> right){
			R -> parent -> right = nil;
		}
		else if (R == root){
			root = nil;
		}
		delete(R);
		num_pairs--;
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if (R == nil || k == R -> key){
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
Dictionary::Node* Dictionary::findMin(Node* R){
	if (R != nil){
		while (R -> left != nil){
			R = R -> left;	
		}
	}
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	if (R != nil){
		while (R -> right != nil){
			R = R -> right;
		}
	}
	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if (N -> right != nil){
		return findMin(N -> right);
	}
	Node* y = N -> parent;
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
Dictionary::Node* Dictionary::findPrev(Node* N){
	if (N -> left != nil){
		return findMax(N -> left);
	}
	Node* y = N -> parent;
	while (y != nil && N == y -> left){
		N = y;
		y = y -> parent;
	}
	return y;
}


void Dictionary::Transplant(Node* U, Node* V){
	if (U -> parent == nil){
		this -> root = V;
	}
	else if (U == U -> parent -> left){
		U -> parent -> left = V;
	}else{
		U -> parent -> right = V;
	}
	if (V != nil){
		V -> parent = U -> parent;
	}
}
// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
	// set y
	Node* Y = N -> right;
	// turn y's left subtree into N's right subtree
	N -> right = Y -> left; 
	if (Y -> left != nil){    // not necessary if using sentinal nil node
		Y -> left -> parent = N;
	}
	// link y's parent to N
	Y -> parent = N -> parent;
	if (N -> parent == nil){
		root = Y;
	}
	else if (N == N -> parent -> left){
		N -> parent -> left = Y;
	}
	else{ 
		N -> parent -> right = Y;
	}
	// put N on y's left
	Y -> left = N;
	N -> parent = Y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
	// set y
	Node* Y = N -> left; 	// turn y's right subtree into N's left subtree
	N -> left = Y -> right 
	if (Y -> right != nil){  // not necessary if using sentinal nil node
		Y -> right -> parent = N;
	}
	// link y's parent to N
	Y -> parent = N -> parent;
	if (N -> parent == nil){
		root = Y;
	}
	else if (N == N -> parent -> right){
		N -> parent -> right = Y;
	}else{ 
		N -> parent -> left = Y;
	}
	// put N on y's right
	Y -> right = N;
	N -> parent = Y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
	while (N -> parent -> color == RED){
		if (N -> parent == N -> parent -> parent -> left){
			Node* Y = N -> parent -> parent -> right;
			if (Y -> color == RED){
				N -> parent -> color = BLK;              // case 1
				Y -> color = BLK;                     // case 1
				N -> parent -> parent -> color = RED;         // case 1
				N = N -> parent -> parent                 // case 1
			}else{ 
				if (N == N -> parent -> right){
					N = N -> parent;                     // case 2
					LeftRotate(N);                 // case 2
				}
			N -> parent -> color = BLK;              // case 3
            N -> parent -> parent -> color = RED;         // case 3
            RightRotate(N -> parent -> parent);     // case 3
			}
		}else{ 
			Y = N -> parent -> parent -> left;
			if (Y -> color == RED){
				N -> parent -> color = BLK;              // case 4
				Y -> color = BLK;                     // case 4
				N -> parent -> parent -> color = RED;         // case 4
				N = N -> parent -> parent;                 // case 4
			}else{ 
				if (N == N -> parent -> left){
					N = N -> parent;                     // case 5
					RightRotate(N);                // case 5
				}
			}
            N -> parent -> color = BLK;              // case 6
            N -> parent -> parent -> color = RED;         // case 6
            LeftRotate(N -> parent -> parent);      // case 6
	root -> color = BLK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
	if (u -> parent == nil){
		root = v;
	}
	else if (u == u -> parent -> left){
		u -> parent -> left = v;
	}else{
		u -> parent -> right = v;
	}
	v -> parent = u -> parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
	Node* W;
	while (N != root && (N -> color == BLK)){
		if N == N -> parent -> left){
			W = N -> parent -> right;
			if (W -> color == RED){
				W -> color = BLK;
				N -> parent -> color = RED;
				LeftRotate(N -> parent);
				W = N -> parent -> right;
			}
			if ((W -> left -> color == BLK) && (W -> right -> color == BLK)){
				W -> color = RED;
				N = N -> parent;
			}else{
				if (W -> right -> color == BLK){
					W -> left -> color = BLK;
					W -> color = RED;
					RightRotate(W);
					W = N -> parent -> right;
				}
				W -> color = N -> parent -> color;
				N -> parent -> color = BLK;
				W -> right -> color = BLK;
				LeftRotate(N -> parent);
				N = root;
			}
		}else{
			W = N -> parent -> left;
			if (W -> color == RED){
				W -> color = BLK;
				N -> parent -> color = RED;
				RightRotate(N -> parent);
				W = N -> parent -> left;
			}
			if ((W -> right -> color == BLK) && (W -> left -> color == BLK)){
				W -> color = RED;
				N = N -> parent;
			}else{
				if (W -> left -> color == BLK){
					W -> right -> color = BLK;
					W -> color = RED;
					LeftRotate(W);
					W = N -> parent -> left;
				}
				W -> color = N -> parent -> color;
				N -> parent -> color = BLK;
				W -> left -> color = BLK;
				RightRotate(N -> parent);
				N = root;
			}
		}
	}
	N -> color = BLK;				
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
	Node* Y = N;
	Node* X;
	Y_OG_col = Y -> color;
	if (N -> left == nil){
		X = N -> right;
		RB_Transplant(N, N -> right);
	}
	else if (N -> right == nil){
		X = N -> left;
		RB_Transplant(N, N -> left);
	}else{
		Y = findMin(N -> right);
		Y_OG_col = Y -> color;
		X = Y -> right;
		if Y -> parent == N){
			X -> parent = Y;
		}else{
			RB_Transplant(Y, Y -> right);
			Y -> right = N -> right;
			Y -> right -> parent = Y;
		}
		RB_Transplant(N, Y);
		Y -> left = N -> left;
		Y -> left -> parent = Y;
		Y -> color = N -> color;
	}
	if (Y_OG_col == BLK){
		RB_DeleteFixUp(X);
	}
}
   
   
// Class Constructors & Destructors ----------------------------------------
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = BLK;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	nil = new Node("nil", 0);
	nil -> left = nil;
	nil -> right = nil;
	current = nil;
	root = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("nil", 0);
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
	if (!hasCurrent()){
		throw std:: logic_error("Dictionary: currentKey(): k does not exist.");
	}
	return current -> key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if (!hasCurrent()){
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
	N -> left = nil;
	N -> right = nil;
	while (R != nil){
		y = R;
		if (R -> key == k){
			R -> val = v;
			delete(N);
			return;
		}
		if (N -> key < R -> key){
			R = R -> left;
		}else{
			R = R -> right;
		}
	}
	N -> parent = y;
	num_pairs++;
	if (y == nil){
		root = N;
	}
	else if (N -> key < y -> key){
		y -> left = N;
	}else{
		y -> right = N;
	}
	if (contains(N -> key)){
		int value = getValue(N -> val) + 1;
		setValue(N -> k, value);
	}else{
		setValue(N -> k, 1);
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
	RB_Delete(del);
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
	if (!hasCurrent()){
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
	if (!hasCurrent()){
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
	string str1 = "";
	string str2 = "";
	this -> inOrderString(str1, this -> root);
	D.inOrderString(str2, D.root);
	if (str1 != str2){
		return false;
	}
	return true;
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
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if (this != &D){
		Dictionary temp = D;
		
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this; //not finished.
}