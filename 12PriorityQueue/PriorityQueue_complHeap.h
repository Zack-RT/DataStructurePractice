#pragma once
// 逻辑上为满二叉树，物理实现上使用vector——满二叉堆
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
	Rank percolateDown(Rank n, Rank i); //下滤
	Rank percolateUp(Rank i); //上滤
	void heapify(Rank n); //Floyd建堆法
public:
	PQ_complHeap(T* A, Rank n) { //批量构造
		this->copyFrom(A, 0, n); 
		heapify(n); } 
	void insert(T);
	T getMax() { return this->_elem[0]; } //取出堆顶
	T delMax(); //删除堆顶
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
	//	percolateUp(i); //建堆可看作像是逐个插入O(nlogn)效率不高
	//}
	for (int i = lastInterNode(this->_size); i >= 0; --i) {
		percolateDown(n, i); // 自下而上的下滤各个节点
	}
}