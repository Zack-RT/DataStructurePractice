#pragma once
#define DEBUG
#include "ListNode.hpp"
#include <iostream>
#include <cstdlib>

template <typename T> class List 
{
private:
	int _size; LNPosi<T> header; LNPosi<T> trailer;
protected:
	void init();
	int clear();
	void copyNodes(LNPosi<T>, int);
	void merge(LNPosi<T>&, int, LNPosi<T>, int);
	void mergeSort(LNPosi<T>&, int);
	void selectionSort(LNPosi<T>, int);
	void insertionSort(LNPosi<T>, int);
public:
	//构造
	List() { init(); }
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
	~List();
#ifdef DEBUG
	void PrintElem() const
	{
		std::cout << "Rank" << '\t' << "Elements" << std::endl;
		LNPosi<T> p = first(); Rank i = 0;
		for (; p != trailer; p = p->succ) {
			std::cout << i++ << "\t" << p->data << std::endl;
		}
	}
#endif // DEBUG
	//只读接口
	int disordered() const;
	Rank size()const { return _size; }
	bool empty()const { return _size <= 0; }
	T& operator[] (Rank r)const;
	bool valid(LNPosi<T> p)const
	{
		return p && (trailer != p) && (header != p);
	}
	LNPosi<T> first()const { return header->succ; }
	LNPosi<T> last()const { return trailer->pred; }
	LNPosi<T> find(T const& e, int n, LNPosi<T> p)const;
	LNPosi<T> find(T const& e)const { return find(e, _size, trailer); }
	LNPosi<T> search(T const& e, int n, LNPosi<T> p)const;
	LNPosi<T> search(T const& e)const { return search(e, _size, trailer); }
	LNPosi<T> selectMax(LNPosi<T> p, int n)const;
	LNPosi<T> selectMax()const { return selectMax(header->succ, _size); }
	//可写接口
	LNPosi<T> insertAsFirst(T const& e);
	LNPosi<T> insertAsLast(T const& e);
	LNPosi<T> insertAfter(LNPosi<T> p, T const& e);
	LNPosi<T> insertBefore(LNPosi<T> p, T const& e);
	T remove(LNPosi<T> p);
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); }
	void sort(LNPosi<T> p, int n);
	void sort() { return sort(first(), _size); }
	int deduplicate();
	int uniquify();//comparison
//	void reverse();
	//遍历
	void traverse(void(*visit)(T& e));
//	template<typename VST> void traverse(VST visit);
};


template<typename T>
T& List<T>::operator[] (Rank r)const {
	LNPosi<T> p = first();
	while (0 < r--) p = p->succ;
	return p->data;
}

template <typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (_size) remove(header->succ);
	return oldSize;
}

template<typename T>
void List<T>::copyNodes(LNPosi<T> p, int n) {
	init();
	while (n--) { insertAsLast(p->data); p = p->succ; }
}

template <typename T>
int List<T>::deduplicate() {//剔除无序列表中的重复节点
	if (_size < 2) return 0;
	int oldSize = _size; Rank r = 0;
	LNPosi<T> p = header;
	while (trailer != (p = p->succ)) {
		LNPosi<T>q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template <typename T>
int List<T>::disordered() const {
	int cnt = 0;
	LNPosi<T> p = first();
	while (p != trailer->pred) {
		if (p->data > p->succ->data)
			cnt++;
		p = p->succ;
	}
	return cnt;
}

//在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
template <typename T>
LNPosi<T> List<T>::find(T const& e, int n, LNPosi<T> p)const {
	while (n--)
		if ((p = p->pred)->data == e) return p;
	return nullptr;
}

template<typename T>
void List<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	_size = 0;
}

template <typename T>
LNPosi<T> List<T>::insertAsFirst(T const& e) {
	_size++; return header->insertAsSucc(e);
}

template <typename T>
LNPosi<T> List<T>::insertAsLast(T const& e) {
	_size++; return trailer->insertAsPred(e);
}

template <typename T>
LNPosi<T> List<T>::insertAfter(LNPosi<T> p, T const& e) {
	_size++; return p->insertAsSucc(e);
}

template <typename T>
LNPosi<T> List<T>::insertBefore(LNPosi<T> p, T const& e) {
	_size++; return p->insertAsPred(e);
}

template <typename T>
void List<T>::insertionSort(LNPosi<T> p, int n) {
	std::cout << "insertionSort..." << std::endl;
	for (int r = 0; r < n; r++) {
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ; remove(p->pred);
	}
}

//当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
template <typename T>
void List<T>::merge(LNPosi<T>& p, int n, LNPosi<T> q, int m) {
	LNPosi<T> pp = p->pred;
	while (m && n) {
		if (q->data < p->data) {
			q = q->succ;
			insertBefore(p, remove(q->pred));
			m--;
		}
		else {
			p = p->succ; n--;
		}
	}
	p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(LNPosi<T>& p, int n) {
	if (n < 2) return;
	LNPosi<T> q = p; int m = n >> 1;
	for (int i = 0; i < m; i++) q = q->succ;
	mergeSort(p, m); mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template <typename T>
T List<T>::remove(LNPosi<T> p) {
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; _size--;
	return e;
}

template <typename T>
LNPosi<T> List<T>::search(T const& e, int n, LNPosi<T> p)const {
	std::cout << "searching for " << e << std::endl;
	while (0 <= n--) {//需返回不大于e的node位置，可能会范围head 需要0<=
		std::cout << p->pred->data;
		if ((p = p->pred)->data <= e) break;
		std::cout << std::endl;
	}
	return p;
}

template <typename T>//从起始于位置p的n个元素中选出最大者
LNPosi<T> List<T>::selectMax(LNPosi<T> p, int n)const {
	LNPosi<T> max = p;
	while (--n)
		if (max->data <= (p = p->succ)->data) max = p;
	return max;
}

template <typename T>
void List<T>::selectionSort(LNPosi<T> p, int n) {
	LNPosi<T> lo = p->pred; LNPosi<T> hi = p;
	for (int i = 0; i < n; i++) hi = hi->succ;
	while (1 < n) {
		LNPosi<T> max = selectMax(lo->succ, n);
		insertBefore(hi, remove(max));
		hi = hi->pred; n--;
	}
}

template <typename T>
void List<T>::sort(LNPosi<T> p, int n) {
	switch (rand() % 3) {
	case 1: insertionSort(p, n); break;
	case 2: selectionSort(p, n); break;
	default: mergeSort(p, n); break;
	}
}

template <typename T>
List<T>::List(List<T> const& L) {
	copyNodes(L.first(), _size);
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, int n) {
	LNPosi<T> p = L.first();
	while (n--) p = p->succ;
	copyNodes(p, n);
}

template <typename T>
List<T>::~List() {
	clear(); delete header; delete trailer;
}

template <typename T>
void List<T>::traverse(void(*visit)(T& e)) {
	LNPosi<T> p = header;
	while ((p = p->succ) != trailer)
		visit(p->data);
}

//template <typename T, typename VST>
//void List<T>::traverse(VST visit) {
//	LNPosi<T> p = header->succ
//	for (; p != trailer; p = p->succ)
//		visit(p->data);
//}

template <typename T>
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int oldSize = _size;
	LNPosi<T> p = first();
	while (trailer != p->succ) {
		(p->data == p->succ->data) ?
			remove(p->succ) : p = p->succ;
	}
	return oldSize - _size;
}
