#pragma once
#include "ListNode.cpp"
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T> class List {
private:
	int _size; LNPosi(T) header; LNPosi(T) trailer;
protected:
	void init();
	int clear();
	void copyNodes(LNPosi(T), int);
	void merge(LNPosi(T)&, int, LNPosi(T), int);
	void mergeSort(LNPosi(T)&, int);
	void selectionSort(LNPosi(T), int);
	void insertionSort(LNPosi(T), int);
public:
	List() { init(); }
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
	~List();
	//只读接口
	int disordered() const;
	Rank size()const { return _size; }
	bool empty()const { return _size <= 0; }
	T& operator[] (Rank r)const;
	bool valid(LNPosi(T) p)const
	{
		return p && (trailer != p) && (header != p);
	}
	LNPosi(T) first()const { return header->succ; }
	LNPosi(T) last()const { return trailer->pred; }
	LNPosi(T) find(T const& e, int n, LNPosi(T) p)const;
	LNPosi(T) find(T const& e)const { return find(e, _size, trailer); }
	LNPosi(T) search(T const& e, int n, LNPosi(T) p)const;
	LNPosi(T) search(T const& e)const { return search(e, _size, trailer); }
	LNPosi(T) selectMax(LNPosi(T) p, int n)const;
	LNPosi(T) selectMax()const { return selectMax(header->succ, _size); }
	//可写接口
	LNPosi(T) insertAsFirst(T const& e);
	LNPosi(T) insertAsLast(T const& e);
	LNPosi(T) insertAfter(LNPosi(T) p, T const& e);
	LNPosi(T) insertBefore(LNPosi(T) p, T const& e);
	T remove(LNPosi(T) p);
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); }
	void sort(LNPosi(T) p, int n);
	void sort() { return sort(first(), _size); }
	int deduplicate();
	int uniquify();//comparison
	void reverse();
	//遍历
	void traverse(void(*)(T&));
	template<typename VST>
	void traverse(VST&);
};