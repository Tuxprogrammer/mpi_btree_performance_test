/* winmain.cpp
* Author: Spencer Callicott,
* Date: 11-22-2016
*
* Description: This file contains tests to run on the Windows operating system.
* It first makes a binary tree of 100,000 nodes, and then from the size of that 
* tree attempts to calculate and allocate a tree of roughly 10GB. It uses the same
* size to create B Tree of the same size and prints the memory usage as well as timing
* analysis of the findNode algorithm.
*/

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <limits>
#include <chrono>

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#include "BinarySearchTree.h"
#include "BTree.h"

#define MAXRAND MAXINT32-1

#define ITERS 100000
			//673684			//64	MB
			//673684*10			//640	MB
			//673684*10*10		//6.4	GB
			//673684*10*10*10	//64	GB

using namespace std;

int main() {
	srand(std::time(0));
	PROCESS_MEMORY_COUNTERS_EX pmc;

	//:::::BST 10000 Iterations Test:::::
	cout << ":::::BST 10000 Iterations Test:::::" << endl;
	size_t beginMem = 0, endMem = 0, startTime = 0, endTime = 0;

	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	beginMem = pmc.PrivateUsage;
	
	BinarySearchTree<int> the10kBSTTree = BinarySearchTree<int>(MAXRAND/2); //set the root to half the maximum random numbers (maybe this will balance the tree)
	
	startTime = time(0);
	for (int i = 0; i < ITERS - 1; i++) {

		the10kBSTTree.add(rand() % MAXRAND);
	}
	endTime = time(0);

	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	endMem = pmc.PrivateUsage;

	cout << "MEMORY USAGE: " << endMem << " - " << beginMem << " = " << (endMem - beginMem) / (1024 * 1024) << "MB" << endl;
	cout << "TOTAL TIME: " << endTime - startTime << " sec." << endl;
	long HUNMBTEST = (long)(		ITERS *
						(double)	100 / //100MB
						((double)	(endMem - beginMem) / (1024 * 1024)));
	cout << "CALCULATED ITERS FOR 100MB TEST:" << fixed << HUNMBTEST << endl;
	cout << endl;

	//:::::BST 10 GB RAM Test:::::
	cout << ":::::BST 100MB RAM Test:::::" << endl;
	beginMem = 0, endMem = 0, startTime = 0, endTime = 0;

	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	beginMem = pmc.PrivateUsage;

	BinarySearchTree<int> theBSTree = BinarySearchTree<int>(MAXRAND / 2); //set the root to half the maximum random numbers (maybe this will balance the tree)

	startTime = time(0);
	for (int i = 0; i < HUNMBTEST - 1; i++) {
		theBSTree.add(rand() % MAXRAND);
	}
	endTime = time(0);

	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	endMem = pmc.PrivateUsage;

	cout << "MEMORY USAGE: " << endMem << " - " << beginMem << " = " << (endMem - beginMem) / (1024 * 1024) << "MB" << endl;
	cout << "TOTAL TIME: " << endTime - startTime << " sec." << endl;
	cout << endl;

	//theTree.printTree();

	//:::::BTree 10 GB RAM Test:::::
	cout << ":::::BTree 100MB RAM Test:::::" << endl;
	beginMem = 0, endMem = 0, startTime = 0, endTime = 0;
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	beginMem = pmc.PrivateUsage;

	BTree<int> theBTree = BTree<int>(200);

	startTime = time(0);
	for (int i = 0; i < HUNMBTEST - 1; i++) {
		theBTree.add(rand() % MAXRAND);
	}

	endTime = time(0);

	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	endMem = pmc.PrivateUsage;

	cout << "MEMORY USAGE: " << endMem << " - " << beginMem << " = " << (endMem - beginMem) / (1024 * 1024) << "MB" << endl;
	cout << "TOTAL TIME: " << endTime - startTime << " sec." << endl;
	cout << endl;

	//theBTree.printTree();

	srand(2);
	clock_t accSTime = clock();
	for (int i = 0; i < HUNMBTEST; i++) {
		theBSTree.splitNode(rand() % MAXRAND);
	}
	clock_t accETime = clock();

	cout << "BinarySearchTree searched " << HUNMBTEST << " nodes in " << accETime - accSTime << " ms" << endl;

	srand(2);
	accSTime = clock();
	for (int i = 0; i < HUNMBTEST; i++) {
		theBTree.findNode(rand() % MAXRAND);
	}
	accETime = clock();

	cout << "B Tree searched " << HUNMBTEST << " nodes in " << accETime - accSTime << " ms" << endl;

	system("pause");

	theBTree.clearTree();
	return 0;
}