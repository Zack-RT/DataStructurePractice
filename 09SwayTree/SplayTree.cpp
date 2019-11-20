#include "pch.h"
#include "SplayTree.h"

template<typename T>
BNPosi(T) SplayTree<T>::splay(BNPosi(T) v){
	// ���ӽڵ��������
	static inline void attachAsRchild(BNPosi(T) node, BNPosi(T) child);
	// ���ӽڵ��������
	static inline void attachAsLchild(BNPosi(T) node, BNPosi(T) child);

	if (v == nullptr) return v;
	BNPosi(T) p; BNPosi(T) g; // ���ס��游
	while ( (p = v->parent) && (g = p->parent) ){ // ���¶��Ϸ���˫����չ
		BNPosi(T) gg = g->parent; // ÿ��splay֮��p������ԭ���游Ϊ����
		if(isLchild(*v)) //����ͬ��ı���ת˳����������ͬС��
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
		//���������������������������������Խӣ������¸߶ȣ�
		if (gg == nullptr) 
			v->parent = nullptr;
		else 
			(g == gg->lchild) ? gg->lchild = v : gg->rchild = v; 
		BinTree<T>::updateHeight(g); 
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	} //whileѭ����������ʱg==NULL����ԭv�ڵ����Ϊ���ż��p==NULL �� _root

	if((p = v->parent) != nullptr) //��p==_root����ԭ�ڵ����Ϊ����ʱ������Ҫ����һ�ε�����ת
		if (isLchild(*v)) { //zig
			attachAsLchild(p, v->rchild); attachAsRchild(v, p);
		} else{ //zag
			attachAsRchild(p, v->lchild); attachAsLchild(v, p);
		}
	return v; //��ʱ��vΪ��
}

template<typename T>
BNPosi(T)& SplayTree<T>::search(const T & e){
	BNPosi(T) & p = searchIn(BinTree<T>::_root, e, BST<T>::_hot);
	//�������ɹ�������е�ҡ���������������_hotҡ��������
	BinTree<T>::_root = splay((p == nullptr) ? BST<T>::_hot : p);
	return BinTree<T>::_root;
}

template<typename T>
BNPosi(T) SplayTree<T>::insert(const T & e){
	BNPosi(T) & p = SplayTree<T>::search(e); // ����ҡ������search�����м�����splay����
	if (p != nullptr) 
		return nullptr; // �ظ��ڵ㲻����
	BNPosi(T) pp = new BinNode<T>(e);
	if (e < p->data) {
		attachAsLchild(pp, p->lchild); attachAsRchild(pp, p);
	} else {
		attachAsRchild(pp, p->rchild); attachAsLchild(pp, p);
	}
	return BinTree<T>::_root = pp;
}


/*˼·1������BST��removeɾ���ڵ����ҡ��_hot�ڵ�������
template<typename T>
bool SplayTree<T>::remove(const T & e){
	if (BST<T>::remove(e)) {
		splay(BST<T>::_hot); return true;
	}
	return false;
}��Ȼ������ӷ�ף����ԸĽ�*/

template<typename T> // �Ľ���������������һ����С�Ľڵ������
bool SplayTree<T>::remove(const T & e){
	if (BinTree<T>::_root == nullptr || e != SplayTree<T>::search(e))
		return false;
	// ��ʱ�ٶ�e�Ѿ�ת��������
	BNPosi(T) w = BinTree<T>::_root;
	if (!hasLchild(*BinTree<T>::_root)) { // ��������Ϊ�գ�ֱ��ɾ��e����
		BinTree<T>::_root = BinTree<T>::_root->rchild;
		delete BinTree<T>::_root->parent;
		BinTree<T>::_root->parent = nullptr;
	}
	else if (!hasRchild(*BinTree<T>::_root)) { // ��������Ϊ�գ�ֱ��ɾ��e����
		BinTree<T>::_root = BinTree<T>::_root->lchild;
		delete BinTree<T>::_root->parent;
		BinTree<T>::_root->parent = nullptr;
	}
	else { // �����������ǿ�
		BNPosi(T) lTree = BinTree<T>::_root->lchild; // �ݴ�������
		lTree->parent = nullptr;				// ��������
		BinTree<T>::_root->lchilde = nullptr;	// ��root��ʱ�ָ�
		BinTree<T>::_root = BinTree<T>::_root->rchild; // ������������
		SplayTree<T>::search(w->data);	// ��һ�ζ�ԭroot�ڵ�Ĳ��ң���������ͬ�ڵ㣩�ض�ʧ�ܣ�����ԭ����������С�Ľڵ��ת��������
		BinTree<T>::_root->lchild = lTree; // ��β���Ҳ������������
		lTree->parent = BinTree<T>::_root; // ��ԭ���ָ������������������
	}
	delete w;
	BinTree<T>::_size--;
	if (BinTree<T>::_root) // �ǵø��¸߶�
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
