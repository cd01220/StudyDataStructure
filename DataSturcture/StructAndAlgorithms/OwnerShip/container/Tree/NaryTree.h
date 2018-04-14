#ifndef _NARY_TREE_H_
#define _NARY_TREE_H_

#include ".\Tree.h"
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h" //LinkedListģ����
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
	//modefied start at 2005-3-31 �������ϵ�Դ���룬����ͨ������
	//  ��Ϊ������麯��û�б����塣
	NaryTree& Subtree (unsigned int) const;
	//modefied start at 2005-3-31 
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void AttachSubtree (unsigned int, NaryTree&);
    virtual NaryTree& DetachSubtree (unsigned int);

	//������麯����
    bool IsEmpty () const;
    bool IsLeaf () const;
	void Purge ();
	unsigned int Degree () const;
};

#endif //_NARY_TREE_H_