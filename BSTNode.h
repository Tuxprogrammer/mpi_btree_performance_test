/* BSTNode.h
* Author: Spencer Callicott
* Date: 11-22-2016
*
* Description: Description for a Binary Search Tree Node of arbitrary type,
* can initialize a new node one of four ways, or change the data of a node.
*/

#pragma once

template<typename T>
class BSTNode {
public:
	T data;
	BSTNode<T> *parent, *left, *right;

	BSTNode();
	
	BSTNode(T first);
	BSTNode(T first, BSTNode<T>* linkParent);

	BSTNode(T first, BSTNode<T>* linkParent, BSTNode<T>* linkLeft, BSTNode<T>* linkRight);

	~BSTNode();

	bool setData(T newdata);
	
};

#include "BSTNode.hpp"