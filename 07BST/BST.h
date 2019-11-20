#pragma once
#include "../BinaryTree/BinTree.cpp"

template <typename T>
class BST :public BinTree<T> {
public:
	virtual BNPosi(T) & search(const T&);
	virtual BNPosi(T) & insert(const T&);
	virtual bool remove(const T&);
protected:
	BNPosi(T) _hot;	//查找成功指向命中节点的父节点，查找失败指向最后一次访问的节点
	BNPosi(T) connect34(BNPosi(T) p1, BNPosi(T) p2, BNPosi(T) p3, \
		BNPosi(T) t1, BNPosi(T) t2, BNPosi(T) t3, BNPosi(T) t4);
	BNPosi(T) rotateAt(BNPosi(T) v);
};
