#pragma once
#include "../07BST/BST.cpp"

template <typename T>
class AVLTree : public BST<T> {
public:	//��д������ɾ��������Ľӿ�ֱ�Ӽ̳�ʹ��
	virtual BNPosi(T) & insert(const T &);
	virtual bool remove(const T &);
};