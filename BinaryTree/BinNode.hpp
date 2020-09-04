#pragma once
#include "../03Stack/Stack_Vector.hpp"
#include "../04Queue/Queue_List.hpp"
#include <queue>;
template <typename T> struct BinNode;
template <typename T> using BNPosi = BinNode<T>* ;
// #define BNPosi<T> BinNode<T>*				//�ڵ�λ��

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
	BNPosi<T> succ(void);	//����������µģ�ֱ�Ӻ��

	template <typename VST> void travLevel(VST visit);	//��α���
	template <typename VST> void travPre(VST visit);	//ǰ�����
	template <typename VST> void travIn(VST visit);		//�������
	template <typename VST> void travPost(VST visit);	//�������
	template <typename VST> void travPre2(VST visit);	//ǰ�����������
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

template <typename T> //����x��������·ѹջ
static void pushAlongLeft(BNPosi<T> x, Stack<BNPosi<T>>& s) {
	while (x != nullptr)
	{
		s.push(x); x = x->lchild;
	}
}

template <typename T, typename VST>
static void visitAlongLeft(BNPosi<T> x, VST visit, Stack<BNPosi<T>>& s) {
	//	if (x == nullptr)	return;		��while��ʵû��Ҫif�п�
	while (x != nullptr) {	//��������·��������;�ڵ��Һ�������ջ
		visit(x->data);
		s.push(x->rchild);	//��ʹnullptr��ջҲ�޷�
		x = x->lchild;
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travPre2(VST visit) {
	Stack<BNPosi<T>> s;
	BNPosi<T> p = this;
	while (true) {	//ȡ�������ջ��������������visitAlongLeft
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
void BinNode<T>::travPost(VST visit) {	//���ֱ����еݹ�ʵ�������ѵģ�����Ҫ��
	BNPosi<T> p = this;
	BNPosi<T> lastVisited = nullptr;	//��¼���һ�η��ʵĽڵ�
	Stack<BNPosi<T>> s;
	while (true) {
		pushAlongLeft(p, s);
		if (s.empty()) break;
		p = s.top();
		if (p->rchild && p->rchild != lastVisited)
			p = p->rchild;	//δ���������ѹջ
		else {	//���ʹ�������ֽڵ�
			visit(p->data);	s.pop();
			lastVisited = p;	p = nullptr;
		}
	}
}
