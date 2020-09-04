#pragma once
#include "../02List/List.hpp"

template <typename T>
class Queue : public List<T> {
public:
	void push(const T& e) { List<T>::insertAsLast(e); }
	T pop() { return List<T>::remove(List<T>::last()); }
	T& front() { return List<T>::first()->data; }
};