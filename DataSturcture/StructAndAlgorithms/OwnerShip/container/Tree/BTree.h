#ifndef _BTREE_H_
#define _BTREE_H_

#include ".\MWayTree.h"   //class MWayTree基类

class BTree : public MWayTree
{
    BTree* parent;   //指向父节点。

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

    //added by liuhao. 2005-12-08 for 在BTree的成员函数中，多处需要访问
    //subtree 成员， 每次都得将其从MWayTree& 手动转换成BTree&， 故重载Subtree()
    //函数。以使每次使用时，直接调用本函数既可。
    BTree& Subtree (unsigned int i) const;

protected:
    //added by liuhao 2005-12-6
    void LLRotation (unsigned int, unsigned int);
    void RRRotation (unsigned int, unsigned int);
    void Unite(unsigned int, unsigned int, unsigned int);  //合并两个节点。
    void Balance ();
};

#endif //_BTREE_H_