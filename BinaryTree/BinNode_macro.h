#pragma once
//关于BinNode及其派生的一些宏

//结点的性态
#define stature(p) ((p)? (p)->height : -1)	//约定:空树高度 = -1
#define isRoot(x) ( ! ( (x).parent ) )
#define isLchild(x) ( ! isRoot(x) && ( & (x) == (x).parent->lchild ) )
#define isRchild(x) ( ! isRoot(x) && ( & (x) == (x).parent->rchild ) )
#define hasParent(x) ( ! isRoot(x) )
#define hasLchild(x) ( (x).lchild )
#define hasRchild(x) ( (x).rchild )
#define hasChild(x) ( hasLchild(x) || hasRchild(x) )
#define hasBothChild(x) ( hasLchild(x) && hasRchild(x) )
#define isLeaf(x) ( ! hasChild(x) )

//节点关系
#define brother(p)/*兄弟*/\
	( isLchild( * (p) ) ? (p)->parent->rchild : (p)->parent->lchild )
#define uncle(p)/*叔叔*/\
	( isLchild( * ( (p)->parent ) ? (p)->parent->parent->rchild : (p)->parent->parent->lchild )
#define fromParentTo(x)/*来自父亲的引用*/\
	( isRoot(x) ? this->_root : ( isLchild(x) ? (x).parent->lchild : (x).parent->rchild ) )

//AVLTree
#define Balanced(x) (stature((x).lchild) == stature((x).rchild))	//理想平衡
#define BalFac(x) (stature((x).lchild) - stature((x).rchild))		//平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))		//是否平衡
//更高的孩子节点，等高返回左孩子
#define tallerChild(p) (stature( (p)->rchild ) > stature( (p)->lchild ) ? (p)->rchild : (p)->lchild )