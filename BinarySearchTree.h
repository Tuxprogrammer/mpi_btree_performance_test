/* BinarySearchTree.h
* Author: Spencer Callicott
* Date: 11-22-2016
*
* Description: Abstracted functions for a Binary Search Tree of arbitrary type,
* handles functions to add, remove, findNode, and printTree the tree.
*
*/
#pragma once
#include "BSTNode.h"

template<typename T>
class BinarySearchTree {
public:
	BSTNode<T>* root;

	BinarySearchTree();
	BinarySearchTree(const T first);
	BinarySearchTree(const T elements[], const int asize);

	bool add(const T newVal);
	bool remove(const T oldVal);
	BSTNode<T>* splitNode(const T val);

	void printTree();

	~BinarySearchTree();

private:
	void DeleteNodes(BSTNode<T>* node);
	void printTree(BSTNode<T>* node);
};

#include "BinarySearchTree.hpp"