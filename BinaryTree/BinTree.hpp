#pragma once

#include "BinNode.hpp"

template <typename T>
class BinTree{
protected:
	int _size;
	BNPosi<T> _root;
	virtual int updateHeight(BNPosi<T> x);
	void updateHeightAbove(BNPosi<T> x);
	void clear(BNPosi<T> x);
public:
	BinTree() :_size(0), _root(nullptr) {}
	~BinTree() { clear(_root); _root = nullptr; }

	int size()const { return _size; }
	bool empty()const { return !_root; }
//	void printTree()const;
	BNPosi<T> root()const { return _root; }
	BNPosi<T> insertAsRC(BNPosi<T> x, T const& e);
	BNPosi<T> insertAsLC(BNPosi<T> x, T const& e);
	BNPosi<T> insertAsRoot(T const& e);
	BNPosi<T> insertAsRoot(BNPosi<T> x);

	template <typename VST> void travLevel(VST visit);	//层次遍历
	template <typename VST> void travPre(VST visit);	//前序遍历
	template <typename VST> void travIn(VST visit);		//中序遍历
	template <typename VST> void travPost(VST visit);	//后序遍历
};

template <typename T>
int BinTree<T>::updateHeight(BNPosi<T> x) {
	return x->height = 1 + \
		stature(x->lchild) > stature(x->rchild) ? \
		stature(x->lchild) : stature(x->rchild);
}

template <typename T>
void BinTree<T>::updateHeightAbove(BNPosi<T> x) {
	while (x)	//自下而上更新节点高度
	{
		updateHeight(x); x = x->parent;
	}
}

template<typename T>
void BinTree<T>::clear(BNPosi<T> x) {
	if (x == nullptr) return;	//递归基，空树返回
	clear(x->lchild); clear(x->rchild);	//递归删除节点
	delete x;
}

template <typename T>
BNPosi<T> BinTree<T>::insertAsRC(BNPosi<T> x, T const& e) {
	_size++;
	x->insertAsRc(e);
	updateHeightAbove(x);
	return x->rchild;
}

template <typename T>
BNPosi<T> BinTree<T>::insertAsLC(BNPosi<T> x, T const& e) {
	_size++;
	x->insertAsLc(e);
	updateHeightAbove(x);
	return x->lchild;
}

template <typename T>
BNPosi<T> BinTree<T>::insertAsRoot(T const& e) {
	_size++;
	_root = new BinNode<T>(e);
	return _root;
}

template<typename T>
BNPosi<T> BinTree<T>::insertAsRoot(BNPosi<T> x)
{
	if (!x) return nullptr;
	_size++;
	_root = x;
	return _root;
}

template<typename T> template<typename VST>
void BinTree<T>::travLevel(VST visit) {
	if (_root)	_root->travLevel(visit);
}

template<typename T> template<typename VST>
void BinTree<T>::travPre(VST visit) {
	if (_root)	_root->travPre(visit);
}

template<typename T> template<typename VST>
void BinTree<T>::travIn(VST visit) {
	if (_root)	_root->travIn(visit);
}

template<typename T> template<typename VST>
void BinTree<T>::travPost(VST visit) {
	if (_root)	_root->travPost(visit);
}


template <typename T>	//给出前序遍历与中序遍历重构二叉树
BNPosi<T> PreIn(T* preOrder, T* inOrder, int size, BNPosi<T> parent) {
	if (size < 1)	return nullptr;	//节点为空
	BNPosi<T> x = new BinNode<T>(*preOrder, parent);
	if (size == 1) return x;	//递归基，叶子节点
	/*对两个序列进行切分
	寻找preOrder[0]在inOrder中的位置inBound
	inOrder[0, inBound)为左子序列		inOrder[inBound+1, size)为右子序列
	preOrder[1, inBound+1)为左子序列	preOrder[inBound+1, size)为右子序列*/
	int inBound = 0;
	for (T* t = inOrder; *t != *preOrder; t++, inBound++);

	x->lchild = PreIn(preOrder + 1, inOrder, inBound, x);	//递归重构左子树
	x->rchild = PreIn(preOrder + inBound + 1, inOrder + inBound + 1, size - inBound - 1, x);	//递归重构右子树
	return x;
}


template <typename T>	//给出中序遍历与后续遍历重构二叉树
BNPosi<T> InPost(T* inOrder, T* postOrder, int size, BNPosi<T> parent) {
	if (size < 1)	return nullptr;
	BNPosi<T> x = new BinNode<T>(*(postOrder + size - 1), parent);
	if (size == 1)	return x;

	/*对两个序列进行切分：
	寻找postOrder[size-1]在inOrder中的位置inBound
	inOrder[0, inBound)为左子序列		inOrder[inBound+1, size)为右子序列
	postOrder[0, inBound)为左子序列		postOrder[inBound, size-1)为右子序列*/
	int inBound = 0;
	for (T* t = inOrder; *t != postOrder + size - 1; t++, inBound++);

	x->lchild = InPost(inOrder, postOrder, inBound, x);		//递归重构左子树
	x->rchild = InPost(inOrder + inBound + 1, postOrder + inBound, size - inBound - 1, x);		//递归重构右子树
	return x;
}

//
//template <typename T>	//给出先序遍历与后续遍历重构真二叉树（孩子数不为1）
//BNPosi<T> PrePost(T* preOrder, T* postOrder, int size, BNPosi<T> parent) {
//	if (!(size % 2))	exit(1);	//不是真二叉树，错误退出
//	BNPosi<T> x = new BinNode<T>(*preOrder, parent);
//	if (size == 1) return x;	//递归基——post pre都指向同一点
//
//	//对两个序列进行切分
//	int preBound = 0, postBound = 0;
//	/*寻找postOrder[size-2]在preOrder中的位置preBound	
//		[1, preBound)为左子树preOrder			[preBound, size)为右子树preOrder*/
//	for (T* t = preOrder; *t != *(postBound + size - 2); t++, preBound++);
//	/*寻找preOrder[1]在postOrder中的位置postBound	
//		[0, postBound+1)为左子树postOrder		[postBound+1, size-1)为右子树postOrder*/
//	for (T* t = postOrder; *t != *(preOrder + 1); t++, postBound++);
//
//	x->lchild = PrePost(preOrder + 1, postOrder, preBound - 1, x);	//递归重构左子树
//	x->rchild = PrePost(preOrder + preBound, postOrder + postBound + 1, size - preBound, x);	//递归重构右子树
//	return x;
//}
