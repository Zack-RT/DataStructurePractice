#include <iostream>
#include "PriorityQueue_complHeap.h"
#include "../99TestCode/Random.h"
using namespace std;
const int TESTSIZE = 20;

extern int GenerateRandomNumber(int low, int high);

int main() {
	int array[TESTSIZE];
	for (int i = 0; i < TESTSIZE; i++) {
		array[i] = GenerateRandomNumber(11, 99);
	}
	PQ_complHeap<int> testPQ(array, TESTSIZE);
	for (int i = 0; i < TESTSIZE; i++)
		cout << testPQ.delMax() << endl;
	return 0;
}