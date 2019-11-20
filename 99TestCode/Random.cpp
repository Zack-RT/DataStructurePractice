#include "Random.h"
#include "stdafx.h"

void Randomize() {
	srand((unsigned int)time(NULL));
}
//Ëæ»ú»¯

int GenerateRandomNumber(int low, int high) {
	double _d;
	if (low > high) {
		cout << "GenerateRandomNumber: Make sure low < high\n";
		exit(1);
	}
	_d = (double)rand() / ((double)RAND_MAX);
	return (low + (int)(_d*(high - low + 1)));
}

double GenerateRandomReal(double low, double high) {
	double _d;
	if (low > high) {
		cout << "GenerateRandomreal: Make sure low < high\n";
		exit(2);
	}
	_d = (double)rand() / (double)RAND_MAX;
	return (low + _d * (high - low));
}