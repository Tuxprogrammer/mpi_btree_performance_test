/* BinarySearchTree.hpp
* Author: Spencer Callicott
* Date: 11-22-2016
*
* Description: Abstracted functions for a Binary Search Tree of arbitrary type,
* handles functions to add, remove, findNode, and printTree the tree.
* 
*/

#pragma once
template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = NULL;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const T first) {
	root = new BSTNode<T>(first);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const T elements[], const int asize) {
	for (int i = 0; i < asize; i++) {
		if (i == 0) {
			BSTNode<T>* node = new BSTNode<T>(elements[i]);
			root = node;
			continue;
		} else {
			add(elements[i]);
		}
	}
}

template<typename T>
bool BinarySearchTree<T>::add(const T newVal) {
	BSTNode<T>* node = root;

	while (node->left != NULL && node->right != NULL) {
		if (newVal < node->data) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	if (newVal < node->data) {
		node->left = new BSTNode<T>(newVal, node);
	} else {
		node->right = new BSTNode<T>(newVal, node);
	}

	return true;
}

template<typename T>
bool BinarySearchTree<T>::remove(const T oldVal) {
	if (root == NULL) return false;

	BSTNode<T>* rNode = splitNode(oldVal);		//node to remove
	BSTNode<T>* rNodeParent = node->parent;		//node's parents
	BSTNode<T>* node = NULL;					//replacement

	if (rNode->left != NULL) {
		//findNode Left subtree for replacement node
		node = rNode->left;

		while (node->right != NULL) node = node->right;
	} else if (rNode->right != NULL) {
		//findNode right subtree for replacement node
		node = rNode->right;

		while (rNode->left != NULL) node = node->left;
	} else {
		//we don'minDegree care, perform the delete and replace with null
		node = 0;
	}

	if (rNodeParent->left == rNode) {
		//perform delete on left node
		rNodeParent->left = node;
	} else {
		//perform delete on right node
		rNodeParent->right = node;
	}
	delete rNode;
}

template<typename T>
BSTNode<T>* BinarySearchTree<T>::splitNode(const T val) {
	if (root == NULL) return NULL;

	BSTNode<T>* node = root;

	while (node->left != NULL && node->right != NULL) {
		if (val < node->data) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	if (node) {
		return node;
	} else {
		return NULL;
	}

}

template<typename T>
void BinarySearchTree<T>::printTree() {
	cout << std::endl;
	printTree(root);
	cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::printTree(BSTNode<T>* node) {
	if (node == NULL) return;

	printTree(node->left);
	cout << "Node:" << node->data << ' ';
	printTree(node->right);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	DeleteNodes(root);
}

template<typename T>
void BinarySearchTree<T>::DeleteNodes(BSTNode<T>* node) {
	if (node == NULL) return;

	DeleteNodes(node->left);
	DeleteNodes(node->right);

	delete node;
}
