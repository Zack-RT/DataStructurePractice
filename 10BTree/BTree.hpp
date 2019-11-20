#pragma once
#include "BTNode.hpp"
#include "../07BST/BST.cpp"
// ƽ��Ķ�·������

template <typename T> using BTPosi = BTNode<T>*;

template <typename T>
class BTree {
protected:
	int _size; // �ؼ�������
	int _order; // �ؼ���״�
	BTPosi<T> _root;
	BTPosi<T> _hot; // search�����ʵķǿսڵ�
	void solveOverflow(BTPosi<T>); // ͨ�����ѽ��insert�����µ�Overflow
	void solveUnderflow(BTPosi<T>); // ͨ���ϲ����remove�����µ�Underflow
public:
	BTPosi<T> search(const T& e);
	bool insert(const T& e);
	bool remove(const T& e);
};

template <typename T>
BTPosi<T> BTree<T>::search(const T& e) {
	BTPosi<T> v = _root; // �Ӹ��ڵ㿪ʼ
	_hot = nullptr;
	while (v != nullptr){ // ������
		Rank r = v->key.search(e);
		if (0 <= r && e == v->key[r]) // ���ҳɹ�
			return v; // ����
		_hot = v; // ��ǰ�ڵ����ʧ��
		v = v->child[r + 1]; // ������һ��
	}
	return nullptr; // ����ʧ��
}