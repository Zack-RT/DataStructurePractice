#pragma once

typedef int Rank;
#define LNPosi(T) ListNode<T>*

template <typename T> struct ListNode {
	T data;
	LNPosi(T) pred; LNPosi(T) succ;

	ListNode() {}
	ListNode(T e, LNPosi(T) p = nullptr, LNPosi(T) s = nullptr)
		: data(e), pred(p), succ(s) {}

	LNPosi(T) insertAsPred(T const& e);
	LNPosi(T) insertAsSucc(T const& e);
};