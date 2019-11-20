#include "ListNode.h"

template <typename T>
LNPosi(T) ListNode<T>::insertAsPred(T const& e) {
	LNPosi(T) x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;
	return x;
}

template <typename T>
LNPosi(T) ListNode<T>::insertAsSucc(T const& e) {
	LNPosi(T) x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;
}
