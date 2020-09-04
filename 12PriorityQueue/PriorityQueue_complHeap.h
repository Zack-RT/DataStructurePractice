#pragma once
// �߼���Ϊ��������������ʵ����ʹ��vector�����������
#include "PriorityQueue.h"
#include "../Vector/Vector.hpp"
#include <cstdlib>

inline Rank getParent(Rank i) { return ((i - 1) >> 1); }
inline Rank getLchild(Rank i) { return (1 + (i << 1)); }
inline Rank getRchild(Rank i) { return ((1 + i) << 1); }
inline Rank lastInterNode(Rank i) { return (i >> 1) - 1; }

template <typename T> class PQ_complHeap : public Vector<T>, public PriorityQueue<T> 
{
protected:
	Rank percolateDown(Rank n, Rank i); //����
	Rank percolateUp(Rank i); //����
	void heapify(Rank n); //Floyd���ѷ�
public:
	PQ_complHeap(T* A, Rank n) { //��������
		this->copyFrom(A, 0, n); 
		heapify(n); } 
	void insert(T);
	T getMax() { return this->_elem[0]; } //ȡ���Ѷ�
	T delMax(); //ɾ���Ѷ�
};

template<typename T>
inline void PQ_complHeap<T>::insert(T e)
{
	Vector<T>::insert(e);
	percolateUp(Vector<T>::_size - 1);
}

template<typename T>
inline Rank PQ_complHeap<T>::percolateUp(Rank i)
{
	while (getParent(i) >= 0) {
		Rank p = getParent(i);
		if (Vector<T>::_elem[i] < Vector<T>::_elem[p]) break;
		std::swap(Vector<T>::_elem[i], Vector<T>::_elem[p]);
		i = p;
	}
	return i;
}

template<typename T>
inline T PQ_complHeap<T>::delMax()
{
	T maxElem = Vector<T>::_elem[0];
	Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size];
	percolateDown(Vector<T>::_size, 0);
	return maxElem;
}

template<typename T>
inline Rank PQ_complHeap<T>::percolateDown(Rank n, Rank i)
{
	while (getLchild(i) < n && getRchild(i) < n){
		if (Vector<T>::_elem[i] > Vector<T>::_elem[getLchild(i)] &&
			Vector<T>::_elem[i] > Vector<T>::_elem[getRchild(i)]) break;
		Rank bigger = Vector<T>::_elem[getLchild(i)] > Vector<T>::_elem[getRchild(i)] ? getLchild(i) : getRchild(i);
		std::swap(Vector<T>::_elem[i], Vector<T>::_elem[bigger]);
		i = bigger;
	}
	if (getLchild(i) < n && Vector<T>::_elem[i] < Vector<T>::_elem[getLchild(i)]) {
		std::swap(Vector<T>::_elem[i], Vector<T>::_elem[getLchild(i)]);
		i = getLchild(i);
	}
	return i;
}

template<typename T>
inline void PQ_complHeap<T>::heapify(Rank n)
{
	//for (int i = 0; i < n; i++) {
	//	percolateUp(i); //���ѿɿ��������������O(nlogn)Ч�ʲ���
	//}
	for (int i = lastInterNode(this->_size); i >= 0; --i) {
		percolateDown(n, i); // ���¶��ϵ����˸����ڵ�
	}
}