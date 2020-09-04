#pragma once
#include "../07BST/BST.h"

template <typename T>
class AVLTree : public BST<T> {
public:	//重写插入与删除，其余的接口直接继承使用
	virtual BNPosi<T> & insert(const T& e );
	virtual bool remove(const T &);
};

template<typename T>
BNPosi<T>& AVLTree<T>::insert(const T& e) {
	BNPosi(T)& x = BST<T>::search(e);
	if (x != nullptr) return x;	//不插入相同元素
	x = new BinNode<T>(e, BST<T>::_hot);
	//第一次循环必然进入else分支进行高度更新故插入节点无需专门调用updateHeightAbove
	BinTree<T>::_size++;
	//此时插入的x可能使得_hot高度增加，进而导致祖先高度失衡
	for (BNPosi(T) g = BST<T>::_hot; g != nullptr; g = g->parent) {
		if (!AvlBalanced(*g)) {//若失衡，则进行修复
			fromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
			break; //局部平衡之后整体必然也平衡了，终止循环
		}
		else //if & else互斥，确保每次AvlBalanced时g的高度都是最新的
			BinTree<T>::updateHeight(g);
	}
	return x;//返回非引用
}

template<typename T>
bool AVLTree<T>::remove(const T& e) {
	BNPosi(T)& x = BST<T>::search(e);
	if (x == nullptr) return false;
	removeAt(x, BST<T>::_hot); BinTree<T>::_size--;
	for (BNPosi(T) g = BST<T>::_hot; g != nullptr; g = g->parent)
		//此处还可优化：检查到g->height没变化后即可停止继续向上
		if (!AvlBalanced(*g)) {
			g = fromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
			BinTree<T>::updateHeight(g);
		}
	return true;
}