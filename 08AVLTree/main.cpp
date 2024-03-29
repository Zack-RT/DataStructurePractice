// 08BBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "AVLTree.cpp"
using namespace std;

const int TestSize = 7;
template<typename T> struct print {
	void operator()(T& t) {
		cout << t << " ";
	}
};

int main(){
	AVLTree<int> avl;
	int Pre[] = { 36, 27, 6, 58, 53, 46, 69 };
	int In[] = { 6, 27, 36, 46, 53, 58, 69 };
	BNPosi(int) x = nullptr;
	x = PreIn<int>(Pre, In, TestSize, x);
	avl.insertAsRoot(x); avl.travLevel(print<int>());


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
