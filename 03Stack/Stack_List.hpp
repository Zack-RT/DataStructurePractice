#pragma once
#include "../02List/List.hpp"

template<typename T>
class Stack : public List<T> {
public:
	Rank push(T const& e) { List<T>::insertAsLast(e); }
	void pop() { List<T>::remove(last()); }
	T& top() { List<T>::last()->ListNode<T>::data; }
};