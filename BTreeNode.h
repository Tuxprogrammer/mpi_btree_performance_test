/* BTreeNode.h
* Author: Spencer Callicott, 
* Date: 11-22-2016
*
* Description: This header file describes all of the functionality of a BTreeNode,
* used by the BTree class when constructing the tree.
*
* Contains recursive functions to delete, printTree, and findNode the tree as well.
*
* Reference: Adapted from GeeksforGeeks
* http://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
*
* Reference: "Introduction to Algorithms 3rd Edition  (English, Paperback, Al. Cormen)"
* Chapter 18 B-Trees (pg. 488-502)
*/

#pragma once

template<typename T>
class BTreeNode {

public:
	T *keys;
	int minDegree;
	BTreeNode<T> **childrenNodes;
	int numKeys;
	bool leaf;

	BTreeNode(int initMinDeg, bool initLeaf);
	void deleteSubtree();

	void printTree();

	BTreeNode<T> *findNode(T key);
							 
	void add(T key);
	void remove(T key);

	void splitNode(int index, BTreeNode<T> *node);

	void balance(int index);

	
	void merge(int index);
};

#include "BTreeNode.hpp"