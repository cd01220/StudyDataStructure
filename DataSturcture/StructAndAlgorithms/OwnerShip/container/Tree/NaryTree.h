#ifndef _NARY_TREE_H_
#define _NARY_TREE_H_

#include ".\Tree.h"
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h" //LinkedList模板类
//////////////////////////////////////////////////////////////////////////////
//	Class: NaryTree
//////////////////////////////////////////////////////////////////////////////
class NaryTree : public Tree
{
protected:
    Object* key;
    unsigned int const degree;
    Array<NaryTree*> subtree;
public:
    NaryTree (unsigned int);
    NaryTree (unsigned int, Object&);
    ~NaryTree ();

    Object& Key () const;
	//modefied start at 2005-3-31 按照书上的源代码，不能通过编译
	//  因为基类的虚函数没有被定义。
	NaryTree& Subtree (unsigned int) const;
	//modefied start at 2005-3-31 
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void AttachSubtree (unsigned int, NaryTree&);
    virtual NaryTree& DetachSubtree (unsigned int);

	//基类的虚函数。
    bool IsEmpty () const;
    bool IsLeaf () const;
	void Purge ();
	unsigned int Degree () const;
};

#endif //_NARY_TREE_H_