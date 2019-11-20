#include "stdafx.h"
#include "BinNode.h"


template <typename T>
BNPosi(T) BinNode<T>::insertAsLc(T const& e) {
	return lchild = new BinNode<T>(e, this);
}

template <typename T>
BNPosi(T) BinNode<T>::insertAsRc(T const& e) {
	return rchild = new BinNode<T>(e, this);
}

template<typename T>
BNPosi(T) BinNode<T>::succ(void)
{
	BNPosi(T) x = this->rchild;
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
	BNPosi(T) p = this;
	stack<BNPosi(T)> s;
	if (p) s.push(p);
	while (!s.empty()){
		p = s.top();	s.pop();
		if (p->rchild)	s.push(p->rchild);
		if (p->lchild)	s.push(p->lchild);
		visit(p->data);
	}
}

template <typename T> //����x��������·ѹջ
static void pushAlongLeft(BNPosi(T) x, stack<BNPosi(T)>& s) {
	while (x != nullptr)	
	{ s.push(x); x = x->lchild; }
}

template <typename T, typename VST>
static void visitAlongLeft(BNPosi(T) x, VST visit, stack<BNPosi(T)>& s){
//	if (x == nullptr)	return;		��while��ʵû��Ҫif�п�
	while (x != nullptr) {	//��������·��������;�ڵ��Һ�������ջ
		visit(x->data);
		s.push(x->rchild);	//��ʹnullptr��ջҲ�޷�
		x = x->lchild;
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travPre2(VST visit){
	stack<BNPosi(T)> s;
	BNPosi(T) p = this;
	while (true) {	//ȡ�������ջ��������������visitAlongLeft
		visitAlongLeft(p, visit, s);
		if (s.empty())	break;
		p = s.top(); s.pop();	
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travIn(VST visit){
	BNPosi(T) p = this;
	stack<BNPosi(T)> s;
	while (true){
		pushAlongLeft(p, s);
		if (s.empty()) break;
		p = s.top(); s.pop();
		visit(p->data);	p = p->rchild;
	}
}

template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST visit){
	BNPosi(T) p = this;
	queue<BNPosi(T)> q;
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
void BinNode<T>::travPost(VST visit){	//���ֱ����еݹ�ʵ�������ѵģ�����Ҫ��
	BNPosi(T) p = this;
	BNPosi(T) lastVisited = nullptr;	//��¼���һ�η��ʵĽڵ�
	stack<BNPosi(T)> s;
	while (true){
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
