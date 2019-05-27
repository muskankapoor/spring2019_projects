// Muskan Kapoor
// FIle: avl_tree_modified.h 
// Assignment 2, March 12, 2019
// class AvlTree modification with its different implementation
// modification is end of file 


#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include "sequence_map.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( ) --> Return smallest item
// Comparable findMax( ) --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted
 
template <typename Comparable>
class AvlTree{
public:
  AvlTree( ) : root{ nullptr }
  { }

  AvlTree( const AvlTree & rhs ) : root{ nullptr }
  {
    root = clone( rhs.root );
  }

  AvlTree( AvlTree && rhs ) : root{ rhs.root }
  {
    rhs.root = nullptr;
  }

  ~AvlTree( )
  {
    makeEmpty( );
  }

  /**
   * Deep copy.
   */
  AvlTree & operator=( const AvlTree & rhs )
  {
    AvlTree copy = rhs;
    std::swap( *this, copy );
    return *this;
  }

  /**
   * Move.
   */
  AvlTree & operator=( AvlTree && rhs )
  {
    std::swap( root, rhs.root );

    return *this;
  }

  /**
   * Find the smallest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMin( ) const
  {
    if( isEmpty( ) )
      throw UnderflowException{ };
    return findMin( root )->element;
  }

  /**
   * Find the largest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMax( ) const
  {
    if( isEmpty( ) )
      throw UnderflowException{ };
    return findMax( root )->element;
  }

  /**
   * Returns true if x is found in the tree.
   */
  bool contains( const Comparable & x ) const
  {
    return contains( x, root );
  }
  
  bool containsString( string x, Comparable *c){
    return containsString(x, root, c);
  }

  bool containsString( string x){
    Comparable c;
    bool value = containsString(x, root, &c);
    return value;
  }
  
  int findCalls(const string x){
    return findCalls(x, root, 0);
  }
  
  /**
   * Test if the tree is logically empty.
   * Return true if empty, false otherwise.
   */
  bool isEmpty( ) const
  {
    return root == nullptr;
  }

  /**
   * Make the tree logically empty.
   */
  void makeEmpty( )
  {
    makeEmpty( root );
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert( const Comparable & x )
  {
    insert( x, root );
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert( Comparable && x )
  {
    insert( std::move( x ), root );
  }

  /**
   * Remove x from the tree. Nothing is done if x is not found.
   */
  void remove( const Comparable & x )
  {
    remove( x, root );
  }

 
  /**
     prints valus of the node 
  **/
  void printValue(const Comparable &x) const {
    printValueHelper(x, root);
  }
  
  int nodeCount(){
    return nodeCount(root);
  }
  
  float internalPath(){
    return internalPath(root, 0);
  }


  int find_calls = 0;
  int getFindCalls(){
    return find_calls;
  }


  int remove_calls = 0;
  int getRemoveCalls(){
    return remove_calls;
  }


  int removes = 0;
  int getRemoves(){
    return removes;
  }
  

  int removeCalls(const Comparable & x){
    return removeCalls(x, root, 1);
  }
    
  
private:
  struct AvlNode
  {
    Comparable element;
    AvlNode   *left;
    AvlNode   *right;
    int       height;

    AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
      : element{ ele }, left{ lt }, right{ rt }, height{ h } { }

    AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
      : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
  };

  AvlNode *root;
  int nodeCount(AvlNode *t){
    if(t == NULL) return 0;
    return (nodeCount(t->left) + nodeCount(t->right)) + 1;
  }

  float internalPath(AvlNode *t, int total){
    if(t == NULL) return 0;
    if(t->left == NULL && t->right == NULL){
      return total + 1;
    }
    return total + (internalPath(t->left, total+1) + internalPath(t->right, total+1));
       
  }

  /**
   * Internal method to insert into a subtree.
   * x is the item to insert.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   */
  void insert( const Comparable & x, AvlNode * & t )
  {
    if( t == nullptr )
      t = new AvlNode{ x, nullptr, nullptr };
    else if( x < t->element )
      insert( x, t->left );
    else if( t->element < x )
      insert( x, t->right );
    else {
      t->element.Merge(x);
    }
    balance( t );
  }

  /**
   * Internal method to insert into a subtree.
   * x is the item to insert.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   */
  void insert( Comparable && x, AvlNode * & t )
  {
    if( t == nullptr )
      t = new AvlNode{ std::move( x ), nullptr, nullptr };
    else if( x < t->element )
      insert( std::move( x ), t->left );
    else if( t->element < x )
      insert( std::move( x ), t->right );

    balance( t );
  }

  /**
   * Internal method to remove from a subtree.
   * x is the item to remove.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   */
  void remove( const Comparable & x, AvlNode * & t )
  {
    if( t == nullptr )
      return;   // Item not found; do nothing

    if( x < t->element )
      remove( x, t->left );
    else if( t->element < x )
      remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr ) // Two children
      {
	t->element = findMin( t->right )->element;
	remove( t->element, t->right );
      }
    else
      {
	AvlNode *oldNode = t;
	t = ( t->left != nullptr ) ? t->left : t->right;
	delete oldNode;
      }

    balance( t );
  }
  
  int removeCalls( const Comparable & x, AvlNode * & t, int calls )
  {
    calls++;
    if( t == nullptr )
      return calls;     
    if( x < t->element )
      return removeCalls( x, t->left, calls );
    else if( t->element < x )
      return removeCalls( x, t->right, calls );
    else if( t->left != nullptr && t->right != nullptr ) 
      {
	t->element = findMin( t->right )->element;
	return removeCalls( t->element, t->right, calls );
      }
    else
      {
	removes++;
	AvlNode *oldNode = t;
	t = ( t->left != nullptr ) ? t->left : t->right;
	delete oldNode;
      }
      
    balance( t );
    return calls;
  }

  static const int ALLOWED_IMBALANCE = 1;

  // Assume t is balanced or within one of being balanced
  void balance( AvlNode * & t )
  {
    if( t == nullptr ){
      return;
    }
    if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ){
      if( height( t->left->left ) >= height( t->left->right ) ){
	rotateWithLeftChild( t );
      }
      else {
	doubleWithLeftChild( t );
      }
    }
    else {
      if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ){
	if( height( t->right->right ) >= height( t->right->left ) ){
	  rotateWithRightChild( t );
	}
	else {
	  doubleWithRightChild( t );
	}
      }
    }

    t->height = max( height( t->left ), height( t->right ) ) + 1;
  }

  /**
   * Internal method to find the smallest item in a subtree t.
   * Return node containing the smallest item.
   */
  AvlNode * findMin( AvlNode *t ) const
  {
    if( t == nullptr )
      return nullptr;
    if( t->left == nullptr )
      return t;
    return findMin( t->left );
  }

  /**
   * Internal method to find the largest item in a subtree t.
   * Return node containing the largest item.
   */
  AvlNode * findMax( AvlNode *t ) const
  {
    if( t != nullptr )
      while( t->right != nullptr )
	t = t->right;
    return t;
  }


  /**
   * Internal method to test if an item is in a subtree.
   * x is item to search for.
   * t is the node that roots the tree.
   */
  bool contains( const Comparable & x, AvlNode *t ) const
  {
    if( t == nullptr )
      return false;
    else if( x < t->element )
      return contains( x, t->left );
    else if( t->element < x )
      return contains( x, t->right );
    else
      return true;    // Match
  }
  /****** NONRECURSIVE VERSION*************************
	  bool contains( const Comparable & x, AvlNode *t ) const
	  {
	  while( t != nullptr )
	  if( x < t->element )
	  t = t->left;
	  else if( t->element < x )
	  t = t->right;
	  else
	  return true;    // Match
	  return false;   // No match
	  }
  *****************************************************/
  bool containsString( const string x, AvlNode *t, Comparable *c ) const
  {
    if( t == nullptr )
      return false;
    else if( x < t->element.GetRecognitionSequence() )
      return containsString( x, t->left, c );
    else if( t->element.GetRecognitionSequence() < x )
      return containsString( x, t->right, c );
    else{
      *c = t->element;
      return true;    
    }
  }

  int findCalls( const string x, AvlNode *t, int calls){
    calls++;
    if( t == nullptr )
      return 0;
    else if( x < t->element.GetRecognitionSequence() )
      return findCalls( x, t->left, calls );
    else if( t->element.GetRecognitionSequence() < x )
      return findCalls( x, t->right, calls );
    else{
      return calls;   
    }
  }

  /**
   * Internal method to make subtree empty.
   */
  void makeEmpty( AvlNode * & t )
  {
    if( t != nullptr )
      {
	makeEmpty( t->left );
	makeEmpty( t->right );
	delete t;
      }
    t = nullptr;
  }

  /**
   * Internal method to clone subtree.
   */
  AvlNode * clone( AvlNode *t ) const
  {
    if( t == nullptr )
      return nullptr;
    else
      return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
  }


  /**
     not found 
  **/ 
  void printValueHelper(const Comparable& x, AvlNode *t) const {
    if(t == nullptr) {
      cout << "Not Found" << endl;
    }
    else if(t->element < x) {
      printValueHelper(x, t->right);
    }
    else if(x < t->element) {
      printValueHelper(x, t->left);
    }
    else {
      cout << t->element << endl;
    }
  }

  /**
   * Return the height of node t or -1 if nullptr.
   */
  int height( AvlNode *t ) const
  {
    return t == nullptr ? -1 : t->height;
  }

  int max( int lhs, int rhs ) const
  {
    return lhs > rhs ? lhs : rhs;
  }
  
  /**
   * Rotate binary tree node with left child.
   * For AVL trees, this is a single rotation for case 1.
   * Update heights, then set new root.
   */
  void rotateWithLeftChild( AvlNode * & k2 )
  {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
  }

  /**
   * Rotate binary tree node with right child.
   * For AVL trees, this is a single rotation for case 4.
   * Update heights, then set new root.
   */
  void rotateWithRightChild( AvlNode * & k1 )
  {
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
  }
  
  
  //*********MODIFIED DOUBLE ROTATIONS*********//
  /**
   * Double rotate binary tree node: first left child.
   * with its right child; then node k3 with new left child.
   * For AVL trees, this is a double rotation for case 2.
   * Update heights, then set new root.
   */

  void doubleWithLeftChild( AvlNode * &  k3 ){

    AvlNode *k1 = k3->left;
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) +1;
    k2->height = max( height( k2->right ), k1->height)  +1;
    
    k3->left = k2;
    k2 = k3;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height(k2->left ), height(k2->right)) +1;
    k1->height = max( height(k1->left), k2->height ) +1;
    k3=k1;
    
  }

  
  /**
   * Double rotate binary tree node: first right child.
   * with its left child; then node k1 with new right child.
   * For AVL trees, this is a double rotation for case 3.
   * Update heights, then set new root.
   **/
 
  void doubleWithRightChild( AvlNode * & k1 ) {

    AvlNode *k2 = k1->right;
    AvlNode *k3 = k2->left;
    k2->left = k3->right;
    k3->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) +1;
    k3->height = max(height(k3->left), k2->height) +1;
    
    k1->right = k3;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
    

    
  }
 


};

#endif
