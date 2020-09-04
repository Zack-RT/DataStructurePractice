#pragma once
#include "../03Stack/Stack_Vector.hpp"
#include "../04Queue/Queue_List.hpp"
#include <queue>;
template <typename T> struct BinNode;
template <typename T> using BNPosi = BinNode<T>* ;
// #define BNPosi<T> BinNode<T>*				//节点位置

template <typename T>
struct BinNode{
	BNPosi<T> parent;
	BNPosi<T> lchild;
	BNPosi<T> rchild;
	T data; int height; int size();
	typedef enum { RED, BALCK } RBCOLOR;
	RBCOLOR color;

	BinNode(): parent(nullptr), lchild(nullptr), rchild(nullptr),height(0), color(RED) {}
	BinNode(const T& data, BNPosi<T> parent = nullptr, BNPosi<T> lc = nullptr,\
			BNPosi<T> rc = nullptr, int h = 0, RBCOLOR color = RED):\
		data(data), parent(parent), lchild(lc), rchild(rc), height(h), color(color) {}
	BNPosi<T> insertAsLc(T const&);
	BNPosi<T> insertAsRc(T const&);
	BNPosi<T> succ(void);	//（中序遍历下的）直接后继

	template <typename VST> void travLevel(VST visit);	//层次遍历
	template <typename VST> void travPre(VST visit);	//前序遍历
	template <typename VST> void travIn(VST visit);		//中序遍历
	template <typename VST> void travPost(VST visit);	//后序遍历
	template <typename VST> void travPre2(VST visit);	//前序遍历升级版
};

template <typename T>
BNPosi<T> BinNode<T>::insertAsLc(T const& e) {
	return lchild = new BinNode<T>(e, this);
}

template <typename T>
BNPosi<T> BinNode<T>::insertAsRc(T const& e) {
	return rchild = new BinNode<T>(e, this);
}

template<typename T>
BNPosi<T> BinNode<T>::succ(void)
{
	BNPosi<T> x = this->rchild;
	while (x->lchild) x = x->lchild;
	return x;
}

template <typename T>
int  BinNode<T>::size() {
	int s = 1;
	if (lchild)	s += lchild->size();
	if (rchild)	s += rchild->size();
	return s;
}

template <typename T> template <typename VST>
void BinNode<T>::travPre(VST visit) {
	BNPosi<T> p = this;
	Stack<BNPosi<T>> s;
	if (p) s.push(p);
	while (!s.empty()) {
		p = s.top();	s.pop();
		if (p->rchild)	s.push(p->rchild);
		if (p->lchild)	s.push(p->lchild);
		visit(p->data);
	}
}

template <typename T> //沿着x子树左线路压栈
static void pushAlongLeft(BNPosi<T> x, Stack<BNPosi<T>>& s) {
	while (x != nullptr)
	{
		s.push(x); x = x->lchild;
	}
}

template <typename T, typename VST>
static void visitAlongLeft(BNPosi<T> x, VST visit, Stack<BNPosi<T>>& s) {
	//	if (x == nullptr)	return;		有while其实没必要if判空
	while (x != nullptr) {	//沿左下线路遍历，沿途节点右孩子则入栈
		visit(x->data);
		s.push(x->rchild);	//即使nullptr入栈也无妨
		x = x->lchild;
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travPre2(VST visit) {
	Stack<BNPosi<T>> s;
	BNPosi<T> p = this;
	while (true) {	//取出最后入栈的右子树，对它visitAlongLeft
		visitAlongLeft(p, visit, s);
		if (s.empty())	break;
		p = s.top(); s.pop();
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travIn(VST visit) {
	BNPosi<T> p = this;
	Stack<BNPosi<T>> s;
	while (true) {
		pushAlongLeft(p, s);
		if (s.empty()) break;
		p = s.top(); s.pop();
		visit(p->data);	p = p->rchild;
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST visit) {
	BNPosi<T> p = this;
	Queue<BNPosi<T>> q;
	q.push(p);
	while (!q.empty())
	{
		p = q.front();	q.pop();
		if (p->lchild)	q.push(p->lchild);
		if (p->rchild)	q.push(p->rchild);
		visit(p->data);
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travPost(VST visit) {	//四种遍历中递归实现是最难的，且重要！
	BNPosi<T> p = this;
	BNPosi<T> lastVisited = nullptr;	//记录最后一次访问的节点
	Stack<BNPosi<T>> s;
	while (true) {
		pushAlongLeft(p, s);
		if (s.empty()) break;
		p = s.top();
		if (p->rchild && p->rchild != lastVisited)
			p = p->rchild;	//未访问则继续压栈
		else {	//访问过则访问现节点
			visit(p->data);	s.pop();
			lastVisited = p;	p = nullptr;
		}
	}
}
