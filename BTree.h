/* BTree.h
* Author: Spencer Callicott
* Date: 11-22-2016
*
* Description: Abstracted description header for a BTree of arbitrary type, functions in this class call the root node's
* recursive functions.
*
* Reference: Adapted from GeeksforGeeks
* http://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
*
* Reference: "Introduction to Algorithms 3rd Edition  (English, Paperback, Al. Cormen)"
* Chapter 18 B-Trees (pg. 488-502)
*/

#pragma once
#include "BTreeNode.h"

template<typename T>
class BTree {
private:
	BTreeNode<T> *root;
	int minDegree, maxDegree;

public:
	BTree(int initMinDegree);

	void clearTree();
	
	void printTree();

	BTreeNode<T>* findNode(T key);
	void add(T key);
	void remove(T key);

};
#include "BTree.hpp"