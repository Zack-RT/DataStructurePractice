#pragma once
#include "../07BST/BST.cpp"

template <typename T>
class SplayTree : public BST<T> {
protected:
	// 核心：将v伸展至树根
	BNPosi(T) splay(BNPosi(T) v); 
public:
	//不同于AVL，Splay可能需要search来改变拓扑结构，属于动态操作，需要重写
	virtual BNPosi(T) & search(const T & e); 
	virtual BNPosi(T) insert(const T & e);
	virtual bool remove(const T & e);
};

/*
特点：
	局部性强，缓存命中率极高
	但仍不能保证单次最坏情况的发生，不适用与效率敏感场景
*/