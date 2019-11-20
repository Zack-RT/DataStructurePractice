#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Randomize();	//随机化种子
int GenerateRandomNumber(int low, int high);			//生成制定范围内的随机整数
double GenerateRandomReal(double low, double high);		//生成制定范围内的随机实数


void Randomize() {
	srand((unsigned int)time(NULL));
}
//随机化

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