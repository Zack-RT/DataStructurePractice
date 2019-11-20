#pragma once
#include "../07BST/BST.cpp"

template <typename T>
class AVLTree : public BST<T> {
public:	//重写插入与删除，其余的接口直接继承使用
	virtual BNPosi(T) & insert(const T &);
	virtual bool remove(const T &);
};