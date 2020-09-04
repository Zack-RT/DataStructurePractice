#pragma once
#include "../07BST/BST.h"

template <typename T>
class AVLTree : public BST<T> {
public:	//��д������ɾ��������Ľӿ�ֱ�Ӽ̳�ʹ��
	virtual BNPosi<T> & insert(const T& e );
	virtual bool remove(const T &);
};

template<typename T>
BNPosi<T>& AVLTree<T>::insert(const T& e) {
	BNPosi(T)& x = BST<T>::search(e);
	if (x != nullptr) return x;	//��������ͬԪ��
	x = new BinNode<T>(e, BST<T>::_hot);
	//��һ��ѭ����Ȼ����else��֧���и߶ȸ��¹ʲ���ڵ�����ר�ŵ���updateHeightAbove
	BinTree<T>::_size++;
	//��ʱ�����x����ʹ��_hot�߶����ӣ������������ȸ߶�ʧ��
	for (BNPosi(T) g = BST<T>::_hot; g != nullptr; g = g->parent) {
		if (!AvlBalanced(*g)) {//��ʧ�⣬������޸�
			fromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
			break; //�ֲ�ƽ��֮�������ȻҲƽ���ˣ���ֹѭ��
		}
		else //if & else���⣬ȷ��ÿ��AvlBalancedʱg�ĸ߶ȶ������µ�
			BinTree<T>::updateHeight(g);
	}
	return x;//���ط�����
}

template<typename T>
bool AVLTree<T>::remove(const T& e) {
	BNPosi(T)& x = BST<T>::search(e);
	if (x == nullptr) return false;
	removeAt(x, BST<T>::_hot); BinTree<T>::_size--;
	for (BNPosi(T) g = BST<T>::_hot; g != nullptr; g = g->parent)
		//�˴������Ż�����鵽g->heightû�仯�󼴿�ֹͣ��������
		if (!AvlBalanced(*g)) {
			g = fromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
			BinTree<T>::updateHeight(g);
		}
	return true;
}