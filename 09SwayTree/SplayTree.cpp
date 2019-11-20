#include "pch.h"
#include "SplayTree.h"

template<typename T>
BNPosi(T) SplayTree<T>::splay(BNPosi(T) v){
	// 连接节点的右子树
	static inline void attachAsRchild(BNPosi(T) node, BNPosi(T) child);
	// 连接节点的左子树
	static inline void attachAsLchild(BNPosi(T) node, BNPosi(T) child);

	if (v == nullptr) return v;
	BNPosi(T) p; BNPosi(T) g; // 父亲、祖父
	while ( (p = v->parent) && (g = p->parent) ){ // 自下而上反复双层伸展
		BNPosi(T) gg = g->parent; // 每次splay之后p都将以原曾祖父为父亲
		if(isLchild(*v)) //子孙同侧改变旋转顺序，子孙异侧大同小异
			if (isLchild(*p)) {	//zig-zig
				attachAsLchild(g, p->rchild); attachAsRchild(p, g);
				attachAsLchild(p, v->rchild); attachAsRchild(v, p);
			} else {			//zig-zag
				attachAsLchild(p, v->rchild); attachAsRchild(v, p);
				attachAsRchild(g, v->lchild); attachAsLchild(v, g);
			} else
			if (isRchild(*p)) {	//zag-zag
				attachAsRchild(g, p->lchild); attachAsLchild(p, g);
				attachAsRchild(p, v->lchild); attachAsLchild(v, p);
			} else {			//zag-zig
				attachAsRchild(p, v->lchild); attachAsLchild(v, p);
				attachAsLchild(g, v->rchild); attachAsRchild(v, g);
			} 
		//祖孙三代调整结束，接下来与曾祖做对接，并更新高度：
		if (gg == nullptr) 
			v->parent = nullptr;
		else 
			(g == gg->lchild) ? gg->lchild = v : gg->rchild = v; 
		BinTree<T>::updateHeight(g); 
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	} //while循环结束，此时g==NULL，视原v节点深度为奇或偶，p==NULL 或 _root

	if((p = v->parent) != nullptr) //若p==_root，即原节点深度为奇数时，则需要再做一次单层旋转
		if (isLchild(*v)) { //zig
			attachAsLchild(p, v->rchild); attachAsRchild(v, p);
		} else{ //zag
			attachAsRchild(p, v->lchild); attachAsLchild(v, p);
		}
	return v; //此时的v为根
}

template<typename T>
BNPosi(T)& SplayTree<T>::search(const T & e){
	BNPosi(T) & p = searchIn(BinTree<T>::_root, e, BST<T>::_hot);
	//查找若成功则把命中点摇摆至树根，否则把_hot摇摆至树根
	BinTree<T>::_root = splay((p == nullptr) ? BST<T>::_hot : p);
	return BinTree<T>::_root;
}

template<typename T>
BNPosi(T) SplayTree<T>::insert(const T & e){
	BNPosi(T) & p = SplayTree<T>::search(e); // 调用摇摆树的search，其中集成了splay操作
	if (p != nullptr) 
		return nullptr; // 重复节点不插入
	BNPosi(T) pp = new BinNode<T>(e);
	if (e < p->data) {
		attachAsLchild(pp, p->lchild); attachAsRchild(pp, p);
	} else {
		attachAsRchild(pp, p->rchild); attachAsLchild(pp, p);
	}
	return BinTree<T>::_root = pp;
}


/*思路1：调用BST的remove删除节点后再摇摆_hot节点至树根
template<typename T>
bool SplayTree<T>::remove(const T & e){
	if (BST<T>::remove(e)) {
		splay(BST<T>::_hot); return true;
	}
	return false;
}显然这略显臃肿，可以改进*/

template<typename T> // 改进：在右子树中找一个最小的节点来替代
bool SplayTree<T>::remove(const T & e){
	if (BinTree<T>::_root == nullptr || e != SplayTree<T>::search(e))
		return false;
	// 此时假定e已经转移至树根
	BNPosi(T) w = BinTree<T>::_root;
	if (!hasLchild(*BinTree<T>::_root)) { // 若左子树为空，直接删除e即可
		BinTree<T>::_root = BinTree<T>::_root->rchild;
		delete BinTree<T>::_root->parent;
		BinTree<T>::_root->parent = nullptr;
	}
	else if (!hasRchild(*BinTree<T>::_root)) { // 若右子树为空，直接删除e即可
		BinTree<T>::_root = BinTree<T>::_root->lchild;
		delete BinTree<T>::_root->parent;
		BinTree<T>::_root->parent = nullptr;
	}
	else { // 左右子树均非空
		BNPosi(T) lTree = BinTree<T>::_root->lchild; // 暂存左子树
		lTree->parent = nullptr;				// 将左子树
		BinTree<T>::_root->lchilde = nullptr;	// 与root暂时分割
		BinTree<T>::_root = BinTree<T>::_root->rchild; // 在右子树当中
		SplayTree<T>::search(w->data);	// 做一次对原root节点的查找，（因无相同节点）必定失败，但是原右子树中最小的节点会转移至树根
		BinTree<T>::_root->lchild = lTree; // 这次查找也不会有左子树
		lTree->parent = BinTree<T>::_root; // 将原来分割开的左子树重新连接上
	}
	delete w;
	BinTree<T>::_size--;
	if (BinTree<T>::_root) // 记得更新高度
		BinTree<T>::updateHeight(BinTree<T>::_root);
	return true;
}

template<typename T>
static inline void attachAsLchild(BNPosi(T) node, BNPosi(T) child) {
	node->lchild = child;
	if (child != nullptr)	child->parent = node;
}

template<typename T>
static inline void attachAsRchild(BNPosi(T) node, BNPosi(T) child) {
	node->rchild = child;
	if (child != nullptr)	child->parent = node;
}
