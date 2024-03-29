// 07BST.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BST.h"
using namespace std;

const int TestSize = 7;
template<typename T> struct print{
	void operator()(T& t) {
		cout << t << " ";
	}
};

int main()
{
	BST<int> bst;
	int Pre[] = { 36, 27, 6, 58, 53, 46, 69 };
	int In[] = { 6, 27, 36, 46, 53, 58, 69 };
	BNPosi(int) x = nullptr;  
	x = PreIn<int>(Pre, In, TestSize, x);

	bst.insertAsRoot(x);
	bst.travLevel(print<int>()); cout << endl;
	x = bst.search(43);
	if (x) cout << x->parent->data << endl;
	else cout << "nullptr" << endl;
//	bst.insert(40);
//	bst.travLevel(print<int>()); cout << endl;
	bst.remove(53);
	bst.travLevel(print<int>()); cout << endl;

	return 0;
}
