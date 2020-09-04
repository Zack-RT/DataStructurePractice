#pragma once
#include "../07BST/BST.h"
#include "../BinaryTree/BinNode_macro.h"

template <typename T> class RedBack : public BST<T> {
public:
	BNPosi<T>& insert(const T& e); 
	bool remove(const T& e);
protected:
	void solveDoubleRed(BNPosi<T> x); // ˫������
	void solveDoubleBlack(BNPosi<T> x); //˫������
	int updateHeight(BNPosi<T> x); //�ڸ�
};

template<typename T>
inline int RedBack<T>::updateHeight(BNPosi<T> x)
{
	x->height = std::max<T>(stature(x->lchild), stature(x->rchild));
	if (IsBlack(x)) { x->height++; } // ֻͳ�ƺڽڵ�
	return x->height;
}

template<typename T>
inline BNPosi<T>& RedBack<T>::insert(const T& e)
{
	BNPosi<T>& x = this->search(e);
	if (x != nullptr) return x; //�������ظ�Ԫ��
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); //Ĭ���²����Ϊ��ڵ㣬�ڸ�Ϊ-1
	solveDoubleRed(x);
	return x ? x : this->_hot->parent;
}

template<typename T>
inline void RedBack<T>::solveDoubleRed(BNPosi<T> x)
{
	if (x->parent == nullptr || x->parent->color == BinNode<T>::BALCK) 
		return;
	if (uncle(x)->color == BinNode<T>::BALCK) {
		if (isLchild(x)) {
			if (isLchild(x->parent)) { // zig-zig RRB
				BNPosi<T> gp = x->parent->parent->parent;
				BNPosi<T> g = this->connect34(x, x->parent, x->parent->parent, x->lchild, x->rchild, brother(x), uncle(x));
				g->color = BinNode<T>::BALCK;
				g->lchild->color = BinNode<T>::RED;
				g->rchild->color = = BinNode<T>::RED;
				g->parent = gp;
				if (gp != nullptr) {
					if (isLchild(g)) {
						gp->lchild = g;
					}
					else {
						gp->rchild = g;
					}
				}
			}
			else { //zig-zag RRB
					

			}
		}
	}
}

template<typename T>
inline bool RedBack<T>::remove(const T& e)
{
	return false;
}