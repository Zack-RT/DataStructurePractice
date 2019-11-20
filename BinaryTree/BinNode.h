#pragma once

#define BNPosi(T) BinNode<T>*				//节点位置
using std::stack;
using std::queue;

template <typename T>
struct BinNode{
	BNPosi(T) parent;
	BNPosi(T) lchild;
	BNPosi(T) rchild;
	T data; int height; int size();

	BinNode(): parent(nullptr), lchild(nullptr), rchild(nullptr),height(0) {}
	BinNode(const T& data, BNPosi(T) parent = nullptr, BNPosi(T) lc = nullptr,\
			BNPosi(T) rc = nullptr, int h = 0):\
		data(data), parent(parent), lchild(lc), rchild(rc), height(h) {}
	BNPosi(T) insertAsLc(T const&);
	BNPosi(T) insertAsRc(T const&);
	BNPosi(T) succ(void);	//（中序遍历下的）直接后继

	template <typename VST> void travLevel(VST visit);	//层次遍历
	template <typename VST> void travPre(VST visit);	//前序遍历
	template <typename VST> void travIn(VST visit);		//中序遍历
	template <typename VST> void travPost(VST visit);	//后序遍历
	template <typename VST> void travPre2(VST visit);	//前序遍历升级版
};
