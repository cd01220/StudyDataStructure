#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include ".\Tree.h"
#include ".\StructAndAlgorithms\Object\Wrapper\Wrapper.h"

void PostfixToInfix ();
void GenTreeByInfix(char* in);

class BinaryTree : public Tree
{
protected:
    Object* key;
    BinaryTree* left;
    BinaryTree* right;
public:
    BinaryTree ();
    BinaryTree (Object&); 
    virtual ~BinaryTree ();

    Object& Key () const;
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual BinaryTree& Left () const;
    virtual BinaryTree& Right () const;
    virtual void AttachLeft (BinaryTree&);

    virtual void AttachRight (BinaryTree&);
    virtual BinaryTree& DetachLeft ();
    virtual BinaryTree& DetachRight ();
    //added by liuhao
	virtual void DepthFirstTraversal (PrePostVisitor&) const;

    virtual BinaryTree& Subtree (unsigned int) const;
	virtual int CompareTo (Object const&) const;	
    virtual bool IsEmpty () const;
    virtual bool IsLeaf () const;
	virtual void Purge ();
	virtual unsigned int Degree () const;
};

class BinarySearchTree : public BinaryTree
{
    virtual Object& FindMin () const = 0;
    virtual Object& FindMax () const = 0;
    //原SearchableContainer的成员函数。
    virtual bool IsMember (Object const&) const = 0;
    virtual void Insert (Object&) = 0;
    virtual void Withdraw (Object&) = 0;
    virtual Object& Find (Object const&) const = 0;
};

#endif //_BINARYTREE_H_
