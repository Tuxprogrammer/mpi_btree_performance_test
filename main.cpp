/* main.cpp
* Author: Spencer Callicott
* Date: 11-22-2016
*
* Description: This program tests my implmentation of Binary Search Trees against
*	another implementation of BTrees using MPI and std::clock for timing.
*/

#include <mpi.h>
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <climits>
#include <sys/sysinfo.h>

#include "BinarySearchTree.h"
#include "BTree.h"

#define SEED 5015541290
#define MAXRAND INT_MAX - 1
#define ITERS 100000000

using namespace std;

BinarySearchTree<int> theBSTree = BinarySearchTree<int>(MAXRAND / 2);
BTree<int> theBTree = BTree<int>(20);

long getMemFree() {
    std::string word;
    std::ifstream file("/proc/meminfo");
    while(file >> word) {
        if(word == "MemFree:") {
            long mem;
            if(file >> mem) {
                return mem;
            } else {
                return 0;
            }
        }
        // ignore rest of the line
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 0; // nothing found
}

int main(int argc, char** argv) {
    srand(SEED);

    MPI_Init(NULL, NULL);
    // Get total number of processors
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get current processor number
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	cout << "Processor " << world_rank << " Program start...." << endl;

    int startMem = getMemFree();

	clock_t accSTime = clock();
	for(int i = 0; i < ITERS - 1; i++) {
        theBSTree.add(rand() % MAXRAND);
    }
	clock_t accETime = clock();

    int endMem = getMemFree();
    cout << "Processor " << world_rank << " finished BinarySearchTree in " << (double)(accETime-accSTime) / 1000 / 1000 << " sec." << " MEMORY USAGE: " << (startMem-endMem) / 1024 << "MB" << endl;
    
    startMem = getMemFree();
	accSTime = clock();
	for(int i = 0; i < ITERS - 1; i++) {
        theBTree.insert(rand() % MAXRAND);
    }
	accETime = clock();
	endMem = getMemFree();

	cout << "Processor " << world_rank << " finished BTree in " << (double)(accETime - accSTime) / 1000 / 1000 << " sec." << " MEMORY USAGE: " << (startMem - endMem) / 1024 << "MB" << endl;

    srand(world_rank);
    accSTime = clock();
    for (int i = 0; i < 100000000; i++) {
        theBSTree.findNode(rand() % MAXRAND);
    }
    accETime = clock();

    cout << "Processor " << world_rank << " BinarySearchTree searched 100,000,000 nodes in " << (double)(accETime - accSTime) / 1000 << " ms" << endl;

    srand(world_rank);
    accSTime = clock();
    for (int i = 0; i < 100000000; i++) {
        theBTree.search(rand() % MAXRAND);
    }
    accETime = clock();

    cout << "Processor " << world_rank << " B Tree searched 100,000,000 nodes in " << (double)(accETime - accSTime) / 1000 << " ms" << endl;

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
