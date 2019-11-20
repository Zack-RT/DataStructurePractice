#include "stdafx.h"
#include "BinTree.cpp"
using namespace std;

template<typename T>
struct increase {
	void operator()(T& x)const { cout << x << endl; }
};

const int TEST_SIZE = 7;

int main() {
	BinTree<int> T; BNPosi(int) x = nullptr;
	int pre[] = { 1,2,4,7,5,3,6 };
	int in[] = { 4,7,2,5,1,6,3 };
	int post[] = { 7,4,5,2,6,3,1 };

	x = PreIn<int>(pre, in, TEST_SIZE, x);
	T.insertAsRoot(x);
	T.travLevel(increase<int>());
	cout << "---------------" << endl;
	T.travPost(increase<int>());

	system("pause");
	return 0;
}