#pragma once
#include "../BinaryTree/BinTree.hpp"

template <typename T>
class BST :public BinTree<T> {
public:
	virtual BNPosi<T> & search(const T&);
	virtual BNPosi<T> & insert(const T&);
	virtual bool remove(const T&);
protected:
	BNPosi<T> _hot;	//���ҳɹ�ָ�����нڵ�ĸ��ڵ㣬����ʧ��ָ�����һ�η��ʵĽڵ�
	BNPosi<T> connect34(BNPosi<T> p1, BNPosi<T> p2, BNPosi<T> p3, \
		BNPosi<T> t1, BNPosi<T> t2, BNPosi<T> t3, BNPosi<T> t4);
	BNPosi<T> rotateAt(BNPosi<T> v);
};

template<typename T>
BNPosi<T>& BST<T>::search(const T& e) {
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);
}

template<typename T>//������
inline static BNPosi<T>& searchIn(BNPosi<T>& p, const T& e, BNPosi<T>& _hot) {
	if (p == nullptr || p->data == e) return p;	//��pΪ�ջ����У�����
	_hot = p;
	while (1) {
		BNPosi<T>& x = (e < _hot->data) ? _hot->lchild : _hot->rchild;
		if (x == nullptr || x->data == e) return x;
		_hot = x;
	}
}

/*
template<typename T>//�ݹ��
static BNPosi<T>& searchIn(BNPosi<T>& p, const T & e, BNPosi<T>& _hot) {
	if (p == nullptr || p->data == e) return p;	//��pΪ�ջ����У�����
	_hot = p;	//�ȼ�¼��hot
	return searchIn((e < p->data ? p->lchild : p->rchild), e, _hot);
}
*/

template<typename T>
BNPosi<T>& BST<T>::insert(const T& e) {
	BNPosi<T>& x = search(e);
	if (x == nullptr) {//������Ԫ����ͬ
		x = new BinNode<T>(e, _hot); //xΪ_hot�ĺ��ӵ���ֵ����ֱ�Ӹ�ֵ����
		BinTree<T>::_size++; BinTree<T>::updateHeightAbove(x);
	}
	return x;
}

template<typename T>
bool BST<T>::remove(const T& e) {
	BNPosi<T>& x = search(e);
	if (x == nullptr) return false;
	removeAt(x, _hot);
	BinTree<T>::_size--; BinTree<T>::updateHeightAbove(_hot);
	return true;
}

template<typename T>
BNPosi<T> removeAt(BNPosi<T>& p, BNPosi<T>& hot) {
	BNPosi<T> w = p;
	BNPosi<T> succ = nullptr;
	if (!p->lchild)	succ = p = p->rchild;		//�����ӿգ�ֱ�����Һ��Ӷ���
	else if (!p->rchild) succ = p = p->lchild;	//���Һ��ӿգ�ֱ�������Ӷ���
	else {//�����Һ��Ӿ�����
		T temp; w = w->succ();
		//����Ҫɾ���ڵ�����ֱ�Ӻ�̽���������ת��Ϊ����Ϊ�յ����
		temp = w->data; w->data = p->data; p->data = temp;
		BNPosi<T> x = w->parent;
		(x == p ? x->rchild : x->lchild) = succ = w->rchild;
	}
	hot = w->parent;
	if (succ) succ->parent = hot;
	delete w;
	return succ;
}

template<typename T>
BNPosi<T> BST<T>::rotateAt(BNPosi<T> v) {
	if (v == nullptr) { cout << "\a\nFail to rotate a NULL node\n"; exit(1); }
	BNPosi<T> p = v->parent; BNPosi<T> g = p->parent;
	//����zig(˳������������)&zag(��������������)������ϵ���������ֱ����connect34��
	if (isLchild(*p))
		if (isLchild(*v)) {	// zig-zig
			p->parent = g->parent;
			return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
		}
		else {				// zig-zag
			v->parent = g->parent;
			return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
		}
	else
		if (isRchild(*v)) {	// zag-zag
			p->parent = g->parent;
			return connect34(g, p, v, g->lchild, p->lchild, v->lchild, p->rchild);
		}
		else {				// zag-zig
			v->parent = g->parent;
			return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild);
		}
}

template<typename T>
BNPosi<T> BST<T>::connect34(BNPosi<T> p1, BNPosi<T> p2, \
	BNPosi<T> p3, BNPosi<T> t1, BNPosi<T> t2, BNPosi<T> t3, BNPosi<T> t4) {
	//����������1����2����
	p1->lchild = t1; if (t1 != nullptr) t1->parent = p1;
	p1->rchild = t2; if (t2 != nullptr) t2->parent = p1;
	BinTree<T>::updateHeight(p1);
	//�Һ���������3����4����
	p3->lchild = t3; if (t3 != nullptr) t3->parent = p3;
	p3->rchild = t4; if (t4 != nullptr) t4->parent = p3;
	BinTree<T>::updateHeight(p3);
	//���ڵ��������Һ�������
	p2->lchild = p1; p1->parent = p2;
	p2->rchild = p3; p3->parent = p2;
	BinTree<T>::updateHeight(p2);
	return p2;
}