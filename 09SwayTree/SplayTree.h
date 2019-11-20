#pragma once
#include "../07BST/BST.cpp"

template <typename T>
class SplayTree : public BST<T> {
protected:
	// ���ģ���v��չ������
	BNPosi(T) splay(BNPosi(T) v); 
public:
	//��ͬ��AVL��Splay������Ҫsearch���ı����˽ṹ�����ڶ�̬��������Ҫ��д
	virtual BNPosi(T) & search(const T & e); 
	virtual BNPosi(T) insert(const T & e);
	virtual bool remove(const T & e);
};

/*
�ص㣺
	�ֲ���ǿ�����������ʼ���
	���Բ��ܱ�֤���������ķ�������������Ч�����г���
*/