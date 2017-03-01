/* BSTNode.hpp
* Author: Spencer Callicott
* Date: 11-22-2016
*
* Description: Abstracted functions for a Binary Search Tree Node of arbitrary type, 
* can initialize a new node one of four ways, or change the data of a node.
*/

#pragma once
template<typename T>
BSTNode<T>::BSTNode() {
	parent = NULL;
	left = NULL;
	right = NULL;
}

template<typename T>
BSTNode<T>::BSTNode(T first) {
	parent = NULL;
	left = NULL;
	right = NULL;
	data = first;
}

template<typename T>
BSTNode<T>::BSTNode(T first, BSTNode<T>* linkParent) {
	left = NULL;
	right = NULL;
	data = first;
	parent = linkParent;
}

template<typename T>
BSTNode<T>::BSTNode(T first, BSTNode<T>* linkParent, BSTNode<T>* linkLeft, BSTNode<T>* linkRight) {
	left = linkLeft;
	right = linkRight;
	data = first;
	parent = linkParent;
}

template<typename T>
BSTNode<T>::~BSTNode() {}

template<typename T>
bool BSTNode<T>::setData(T newdata) {
	data = newdata;
	return true;
}