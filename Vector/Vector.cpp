#include "Vector.h"
#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = (hi - lo) * 2];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

//
template <typename T>
void Vector<T>::print()const {
	cout << "The elements of the Vector:" << endl;
	for (int i = 0; i < _size; i++)
		cout << _elem[i] << " ";
	cout << endl;
}

template <typename T>
int Vector<T>::get_size_capacity()const {
	cout << "The size of the Vector: " << _size << endl;
	cout << "The capacity of the Vector: " << _capacity << endl;
	return _capacity;
}


template <typename T>
void Vector<T>::expand() {
	if (_capacity <= DEFAULT_CAPCITY) return;
	if (_capacity < _size << 1) return;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; _elem[i] = oldElem[i++]);
	delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
	if (_capacity <= DEFAULT_CAPCITY) return;
	if (_capacity <= _size << 2) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; _elem[i] = oldElem[i++]);
	delete[] oldElem;
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
	Rank r = lo;
	for (int i = lo + 1; i < hi; i++)
		if (_elem[r] < _elem[i])
			r = i;
	return r;
}

template <typename T>
T& Vector<T>::operator[](Rank t)const {
	return _elem[t];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) {
	if (_elem) delete[] _elem;
	copyFrom(v._elem, 0, v._size);
	return *this;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	while (hi <_size) _elem[lo++] = _elem[hi++];
	_size = lo; shrink();
	return (hi - lo);
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_size++; _elem[r] = e;
	return r;
}

template <typename T>
int Vector<T>::disordered()const {
	int n = 0;
	for (int i = 0; i < _size; i++)
		if (_elem[i] < _elem[i - 1])
			n++;
	return n;
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const {
	while ((lo < hi--) && (_elem[hi] != e));//nice!
	return hi;
}

template <typename T>
void Vector<T>::traverse(void(*visit)(T&)) {
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST & visit)
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size;
	for (int i = 1; i < _size;)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i; shrink();
	return j - i;
}

template <typename T>
Rank binarySearch(const T* e, T const& t, Rank lo, Rank hi) {
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		(t < e[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const {
	return binarySearch(_elem, e, lo, hi);
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			sorted = false;
			std::swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi));
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo;
	int lb = mi - lo; int lc = hi - mi;
	T* B = new T[lb]; T* C = _elem + mi;
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && ((lc <= k) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && ((lb <= j) || (C[k] < B[j])))  A[i++] = C[k++];
	}
	delete[] B;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return;
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi); mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* A = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
		std::swap(A[i - 1], A[std::rand() % i]);
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	int select = 1;
	//cout << "Choose the algorithm you want: \
	    \n 1. Bubble \n 2. Merge " << endl;
//cin >> select;
	if (select == 1)         bubbleSort(lo, hi);
	else if (select == 2)    mergeSort(lo, hi);
	else return;
}