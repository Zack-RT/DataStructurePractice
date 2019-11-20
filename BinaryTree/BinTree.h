#pragma once

#include "BinNode.cpp"

template <typename T>
class BinTree{
protected:
	int _size;
	BNPosi(T) _root;
	virtual int updateHeight(BNPosi(T) x);
	void updateHeightAbove(BNPosi(T) x);
	void clear(BNPosi(T) x);
public:
	BinTree() :_size(0), _root(nullptr) {}
	~BinTree() { clear(_root); _root = nullptr; }

	int size()const { return _size; }
	bool empty()const { return !_root; }
//	void printTree()const;
	BNPosi(T) root()const { return _root; }
	BNPosi(T) insertAsRC(BNPosi(T) x, T const& e);
	BNPosi(T) insertAsLC(BNPosi(T) x, T const& e);
	BNPosi(T) insertAsRoot(T const& e);
	BNPosi(T) insertAsRoot(BNPosi(T) x);

	template <typename VST> void travLevel(VST visit);	//层次遍历
	template <typename VST> void travPre(VST visit);	//前序遍历
	template <typename VST> void travIn(VST visit);		//中序遍历
	template <typename VST> void travPost(VST visit);	//后序遍历
};

template <typename T>	//给出前序遍历与中序遍历重构二叉树
BNPosi(T) PreIn(T* preOrder, T* inOrder, int size, BNPosi(T) parent);
template <typename T>	//给出中序遍历与后续遍历重构二叉树
BNPosi(T) InPost(T* inOrder, T* postOrder, int size, BNPosi(T) parent);
template <typename T>	//给出先序遍历与后续遍历重构真二叉树（孩子数不为1）
BNPosi(T) PrePost(T* preOrder, T* postOrder, int size, BNPosi(T) parent);

