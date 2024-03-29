#pragma once
#include "../Vector/Vector.hpp"

template <typename T>
class Stack : public Vector<T> {
public:
	Rank push(T const & e) { return Vector<T>::insert(e); }
	void pop() { Vector<T>::remove(--Vector<T>::_size-1); }
	T& top() { return  Vector<T>::_elem[Vector<T>::_size-1]; }
};