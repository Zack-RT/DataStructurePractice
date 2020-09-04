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

	template <typename VST> void travLevel(VST visit);	//��α���
	template <typename VST> void travPre(VST visit);	//ǰ�����
	template <typename VST> void travIn(VST visit);		//�������
	template <typename VST> void travPost(VST visit);	//�������
};

template <typename T>
int BinTree<T>::updateHeight(BNPosi<T> x) {
	return x->height = 1 + \
		stature(x->lchild) > stature(x->rchild) ? \
		stature(x->lchild) : stature(x->rchild);
}

template <typename T>
void BinTree<T>::updateHeightAbove(BNPosi<T> x) {
	while (x)	//���¶��ϸ��½ڵ�߶�
	{
		updateHeight(x); x = x->parent;
	}
}

template<typename T>
void BinTree<T>::clear(BNPosi<T> x) {
	if (x == nullptr) return;	//�ݹ������������
	clear(x->lchild); clear(x->rchild);	//�ݹ�ɾ���ڵ�
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


template <typename T>	//����ǰ���������������ع�������
BNPosi<T> PreIn(T* preOrder, T* inOrder, int size, BNPosi<T> parent) {
	if (size < 1)	return nullptr;	//�ڵ�Ϊ��
	BNPosi<T> x = new BinNode<T>(*preOrder, parent);
	if (size == 1) return x;	//�ݹ����Ҷ�ӽڵ�
	/*���������н����з�
	Ѱ��preOrder[0]��inOrder�е�λ��inBound
	inOrder[0, inBound)Ϊ��������		inOrder[inBound+1, size)Ϊ��������
	preOrder[1, inBound+1)Ϊ��������	preOrder[inBound+1, size)Ϊ��������*/
	int inBound = 0;
	for (T* t = inOrder; *t != *preOrder; t++, inBound++);

	x->lchild = PreIn(preOrder + 1, inOrder, inBound, x);	//�ݹ��ع�������
	x->rchild = PreIn(preOrder + inBound + 1, inOrder + inBound + 1, size - inBound - 1, x);	//�ݹ��ع�������
	return x;
}


template <typename T>	//���������������������ع�������
BNPosi<T> InPost(T* inOrder, T* postOrder, int size, BNPosi<T> parent) {
	if (size < 1)	return nullptr;
	BNPosi<T> x = new BinNode<T>(*(postOrder + size - 1), parent);
	if (size == 1)	return x;

	/*���������н����з֣�
	Ѱ��postOrder[size-1]��inOrder�е�λ��inBound
	inOrder[0, inBound)Ϊ��������		inOrder[inBound+1, size)Ϊ��������
	postOrder[0, inBound)Ϊ��������		postOrder[inBound, size-1)Ϊ��������*/
	int inBound = 0;
	for (T* t = inOrder; *t != postOrder + size - 1; t++, inBound++);

	x->lchild = InPost(inOrder, postOrder, inBound, x);		//�ݹ��ع�������
	x->rchild = InPost(inOrder + inBound + 1, postOrder + inBound, size - inBound - 1, x);		//�ݹ��ع�������
	return x;
}

//
//template <typename T>	//���������������������ع������������������Ϊ1��
//BNPosi<T> PrePost(T* preOrder, T* postOrder, int size, BNPosi<T> parent) {
//	if (!(size % 2))	exit(1);	//������������������˳�
//	BNPosi<T> x = new BinNode<T>(*preOrder, parent);
//	if (size == 1) return x;	//�ݹ������post pre��ָ��ͬһ��
//
//	//���������н����з�
//	int preBound = 0, postBound = 0;
//	/*Ѱ��postOrder[size-2]��preOrder�е�λ��preBound	
//		[1, preBound)Ϊ������preOrder			[preBound, size)Ϊ������preOrder*/
//	for (T* t = preOrder; *t != *(postBound + size - 2); t++, preBound++);
//	/*Ѱ��preOrder[1]��postOrder�е�λ��postBound	
//		[0, postBound+1)Ϊ������postOrder		[postBound+1, size-1)Ϊ������postOrder*/
//	for (T* t = postOrder; *t != *(preOrder + 1); t++, postBound++);
//
//	x->lchild = PrePost(preOrder + 1, postOrder, preBound - 1, x);	//�ݹ��ع�������
//	x->rchild = PrePost(preOrder + preBound, postOrder + postBound + 1, size - preBound, x);	//�ݹ��ع�������
//	return x;
//}
