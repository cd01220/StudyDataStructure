#ifndef _BTREE_H_
#define _BTREE_H_

#include ".\MWayTree.h"   //class MWayTree����

class BTree : public MWayTree
{
    BTree* parent;   //ָ�򸸽ڵ㡣

    void InsertPair (Object&, BTree&);
    void AttachKey (unsigned int, Object&);
    void AttachSubtree (unsigned int, MWayTree&);
    Object& InsertKey (unsigned int, Object&);
    BTree& InsertSubtree (unsigned int, BTree&);
    void AttachLeftHalfOf (BTree const&);
    void AttachRightHalfOf (BTree const&, Object&, BTree&);
public:
    BTree (unsigned int);
    BTree (unsigned int, BTree&);

    void Insert (Object&);
    void Withdraw (Object&);

    //added by liuhao. 2005-12-08 for ��BTree�ĳ�Ա�����У��ദ��Ҫ����
    //subtree ��Ա�� ÿ�ζ��ý����MWayTree& �ֶ�ת����BTree&�� ������Subtree()
    //��������ʹÿ��ʹ��ʱ��ֱ�ӵ��ñ������ȿɡ�
    BTree& Subtree (unsigned int i) const;

protected:
    //added by liuhao 2005-12-6
    void LLRotation (unsigned int, unsigned int);
    void RRRotation (unsigned int, unsigned int);
    void Unite(unsigned int, unsigned int, unsigned int);  //�ϲ������ڵ㡣
    void Balance ();
};

#endif //_BTREE_H_