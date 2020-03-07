#pragma once

using Rank = int;
template <typename T> struct ListNode;
template <typename T> using LNPosi = ListNode<T>*;

template <typename T> struct ListNode 
{
	T data;
	LNPosi<T> pred; LNPosi<T> succ;

	ListNode() {}
	ListNode(T e, LNPosi<T> p = nullptr, LNPosi<T> s = nullptr)
		: data(e), pred(p), succ(s) {}

	LNPosi<T> insertAsPred(T const& e);
	LNPosi<T> insertAsSucc(T const& e);
};

template <typename T>
LNPosi<T> ListNode<T>::insertAsPred(T const& e) {
	LNPosi<T> x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;
	return x;
}

template <typename T>
LNPosi<T> ListNode<T>::insertAsSucc(T const& e) {
	LNPosi<T> x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;
}
