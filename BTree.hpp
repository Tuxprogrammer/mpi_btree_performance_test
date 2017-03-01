/* BTree.hpp
* Author: Spencer Callicott
* Date: 11-22-2016
* 
* Description: Abstracted functions for a BTree of arbitrary type, functions in this class call the root node'temp
* recursive functions.
* 
* Reference: Adapted from GeeksforGeeks
* http://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
* 
* Reference: "Introduction to Algorithms 3rd Edition  (English, Paperback, Al. Cormen)"
* Chapter 18 B-Trees (pg. 488-502)
*/

#pragma once

template<typename T>
BTree<T>::BTree(int initMinDegree) {
	root = NULL;
	minDegree = initMinDegree;
	maxDegree = 2 * minDegree - 1;
}

template<typename T>
void BTree<T>::clearTree() {
	root->deleteSubtree();
}

template<typename T>
void BTree<T>::printTree() {
	if (root != NULL) root->printTree();
}

template<typename T>
void BTree<T>::add(T key) {
	if (root == NULL) {
		
		root = new BTreeNode<T>(minDegree, true);
		root->keys[0] = key; 
		root->numKeys = 1;
	} else {
		if (root->numKeys == maxDegree) {
			BTreeNode<T> *temp = new BTreeNode<T>(minDegree, false);

			temp->childrenNodes[0] = root;
			temp->splitNode(0, root);

			int i = (temp->keys[0] < key) ? 1 : 0;
			temp->childrenNodes[i]->add(key);

			root = temp;
		} else {
			root->add(key);
		}
	}
}

template<typename T>
void BTree<T>::remove(T key) {
	if (!root) {
		cout << "The tree is empty\n";
		return;
	}

	// Call the remove function for root
	root->remove(key);

	// If the root node has 0 keys, make its first child as the new root
	//  if it has a child, otherwise set root as NULL
	if (root->numKeys == 0) {
		BTreeNode *tmp = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->childrenNodes[0];

		// Free the old root
		delete tmp;
	}
	return;
}

// function to findNode a key in this tree
template<typename T>
BTreeNode<T>* BTree<T>::findNode(T key) {
	return (root == NULL) ? NULL : root->findNode(key);
}