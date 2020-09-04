#pragma once
#include "../BinaryTree/BinTree.hpp"

template <typename T>
class BST :public BinTree<T> {
public:
	virtual BNPosi<T> & search(const T&);
	virtual BNPosi<T> & insert(const T&);
	virtual bool remove(const T&);
protected:
	BNPosi<T> _hot;	//查找成功指向命中节点的父节点，查找失败指向最后一次访问的节点
	BNPosi<T> connect34(BNPosi<T> p1, BNPosi<T> p2, BNPosi<T> p3, \
		BNPosi<T> t1, BNPosi<T> t2, BNPosi<T> t3, BNPosi<T> t4);
	BNPosi<T> rotateAt(BNPosi<T> v);
};

template<typename T>
BNPosi<T>& BST<T>::search(const T& e) {
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);
}

template<typename T>//迭代版
inline static BNPosi<T>& searchIn(BNPosi<T>& p, const T& e, BNPosi<T>& _hot) {
	if (p == nullptr || p->data == e) return p;	//若p为空或命中，返回
	_hot = p;
	while (1) {
		BNPosi<T>& x = (e < _hot->data) ? _hot->lchild : _hot->rchild;
		if (x == nullptr || x->data == e) return x;
		_hot = x;
	}
}

/*
template<typename T>//递归版
static BNPosi<T>& searchIn(BNPosi<T>& p, const T & e, BNPosi<T>& _hot) {
	if (p == nullptr || p->data == e) return p;	//若p为空或命中，返回
	_hot = p;	//先记录下hot
	return searchIn((e < p->data ? p->lchild : p->rchild), e, _hot);
}
*/

template<typename T>
BNPosi<T>& BST<T>::insert(const T& e) {
	BNPosi<T>& x = search(e);
	if (x == nullptr) {//不允许元素雷同
		x = new BinNode<T>(e, _hot); //x为_hot的孩子的左值引用直接赋值即可
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
	if (!p->lchild)	succ = p = p->rchild;		//若左孩子空，直接用右孩子顶替
	else if (!p->rchild) succ = p = p->lchild;	//若右孩子空，直接用左孩子顶替
	else {//若左右孩子均存在
		T temp; w = w->succ();
		//将需要删除节点与其直接后继交换，问题转化为左孩子为空的情况
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
	//根据zig(顺旋、右上左下)&zag(逆旋、左上右下)排列组合的四种情况分别进行connect34：
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
	//左孩子与子树1子树2连接
	p1->lchild = t1; if (t1 != nullptr) t1->parent = p1;
	p1->rchild = t2; if (t2 != nullptr) t2->parent = p1;
	BinTree<T>::updateHeight(p1);
	//右孩子与子树3子树4连接
	p3->lchild = t3; if (t3 != nullptr) t3->parent = p3;
	p3->rchild = t4; if (t4 != nullptr) t4->parent = p3;
	BinTree<T>::updateHeight(p3);
	//根节点与左孩子右孩子连接
	p2->lchild = p1; p1->parent = p2;
	p2->rchild = p3; p3->parent = p2;
	BinTree<T>::updateHeight(p2);
	return p2;
}