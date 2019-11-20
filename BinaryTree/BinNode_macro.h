#pragma once
//����BinNode����������һЩ��

//������̬
#define stature(p) ((p)? (p)->height : -1)	//Լ��:�����߶� = -1
#define isRoot(x) ( ! ( (x).parent ) )
#define isLchild(x) ( ! isRoot(x) && ( & (x) == (x).parent->lchild ) )
#define isRchild(x) ( ! isRoot(x) && ( & (x) == (x).parent->rchild ) )
#define hasParent(x) ( ! isRoot(x) )
#define hasLchild(x) ( (x).lchild )
#define hasRchild(x) ( (x).rchild )
#define hasChild(x) ( hasLchild(x) || hasRchild(x) )
#define hasBothChild(x) ( hasLchild(x) && hasRchild(x) )
#define isLeaf(x) ( ! hasChild(x) )

//�ڵ��ϵ
#define brother(p)/*�ֵ�*/\
	( isLchild( * (p) ) ? (p)->parent->rchild : (p)->parent->lchild )
#define uncle(p)/*����*/\
	( isLchild( * ( (p)->parent ) ? (p)->parent->parent->rchild : (p)->parent->parent->lchild )
#define fromParentTo(x)/*���Ը��׵�����*/\
	( isRoot(x) ? this->_root : ( isLchild(x) ? (x).parent->lchild : (x).parent->rchild ) )

//AVLTree
#define Balanced(x) (stature((x).lchild) == stature((x).rchild))	//����ƽ��
#define BalFac(x) (stature((x).lchild) - stature((x).rchild))		//ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))		//�Ƿ�ƽ��
//���ߵĺ��ӽڵ㣬�ȸ߷�������
#define tallerChild(p) (stature( (p)->rchild ) > stature( (p)->lchild ) ? (p)->rchild : (p)->lchild )