#pragma once
#include "BTNode.hpp"
#include "../07BST/BST.cpp"
// 平衡的多路搜索树

template <typename T> using BTPosi = BTNode<T>*;

template <typename T>
class BTree {
protected:
	int _size; // 关键码总数
	int _order; // 关键码阶次
	BTPosi<T> _root;
	BTPosi<T> _hot; // search最后访问的非空节点
	void solveOverflow(BTPosi<T>); // 通过分裂解决insert而导致的Overflow
	void solveUnderflow(BTPosi<T>); // 通过合并解决remove而导致的Underflow
public:
	BTPosi<T> search(const T& e);
	bool insert(const T& e);
	bool remove(const T& e);
};

template <typename T>
BTPosi<T> BTree<T>::search(const T& e) {
	BTPosi<T> v = _root; // 从根节点开始
	_hot = nullptr;
	while (v != nullptr){ // 逐层查找
		Rank r = v->key.search(e);
		if (0 <= r && e == v->key[r]) // 查找成功
			return v; // 返回
		_hot = v; // 当前节点查找失败
		v = v->child[r + 1]; // 进入下一层
	}
	return nullptr; // 查找失败
}