#pragma once
#include "../BinaryTree/BinNode.hpp"
#include "../Vector/Vector.hpp"

template <typename T>
struct BTNode{ // B-树节点
	BNPosi(T) parent;
	Vector<T> key;
	Vector<BNPosi(T)> child;

	BTNode() {
		parent = nullptr;
		child.insert(0, nullptr);
	}
	// 此构造仅针对root, 一个key 两个child
	BTNode(const T& e, BNPosi(T) lchild = nullptr, BNPosi(T) rchild = nullptr) { 
		parent = nullptr;
		key.insert(0, e);
		child.insert(0, lchild);
		child.insert(1, rchild);
		if (lchild != nullptr) {
			lchild->parent = this;
		}
		if (rchild != nullptr) {
			rchild->parent = this;
		}
	}
};