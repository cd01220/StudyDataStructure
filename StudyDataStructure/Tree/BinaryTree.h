#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include ".\Tree.h"

void PostfixToInfix ();
void GenTreeByInfix(char* in);

template <class T>
class BinaryTree : public Tree<T>
{
protected:
    T key;
    BinaryTree* left;
    BinaryTree* right;
public:
    BinaryTree();
    BinaryTree(T); 
    virtual ~BinaryTree ();

    T& Key ();
    virtual void AttachKey(T&);
    virtual void DetachKey();
    virtual BinaryTree<T>& Left();
    virtual BinaryTree<T>& Right();

    virtual void AttachLeft(BinaryTree*);
    virtual void AttachRight(BinaryTree*);
    virtual BinaryTree* DetachLeft();
    virtual BinaryTree* DetachRight();

    virtual void DepthFirstTraversal (PrePostVisitor<T>&);
    virtual BinaryTree& Subtree(unsigned int);
	virtual int CompareTo(BinaryTree<T>&);
    virtual bool IsEmpty();
    virtual bool IsLeaf();
	virtual void Purge();
	virtual unsigned int Degree();
};

template <class T>
unsigned int BinaryTree<T>::Degree ()
{
	return 2;
}

template <class T>
T& BinaryTree<T>::Key ()
{
	return key;
}

template <class T>
bool BinaryTree<T>::IsLeaf()
{
	if(IsEmpty())
	{
		return false;
	}
	
	return (left->IsEmpty() && right->IsEmpty());
}

template <class T>
bool BinaryTree<T>::IsEmpty()
{
	return (left == NULL && right == NULL);
}

template <class T>
void BinaryTree<T>::AttachKey(T& key)
{
	if(!IsEmpty())
	{
		throw domain_error("invalid operation");
	}
	
	BinaryTree<T>::key = key;
	left = new BinaryTree();
	right = new BinaryTree();
}

template <class T>
void BinaryTree<T>::DetachKey()
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}
	
	if(!IsLeaf())
	{
		throw domain_error("invalid operation");
	}
	
	delete left;
	delete right;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::Left()
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

	return *left;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::Right()
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

	return *right;
}

//modified by liuhao 2005-11-24。
template <class T>
void BinaryTree<T>::AttachLeft(BinaryTree* subtree)
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

    //左子树不为空，引发异常。
	if(!left->IsEmpty())
	{
		throw domain_error("non-empty subtree present");
	}
	delete left;
	left = subtree;
}

//modified by liuhao 2005-11-24。
template <class T>
void BinaryTree<T>::AttachRight(BinaryTree* subtree)
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

	if(!right->IsEmpty())
	{
		throw domain_error("invalid operatrion");
	}

	delete right;
	right = subtree;
}

template <class T>
BinaryTree<T>* BinaryTree<T>::DetachLeft()
{
	if (IsEmpty ())
	{
		throw domain_error ("invalid operation");
	}
    BinaryTree* result = left;
    left = new BinaryTree;
    return result;
}

template <class T>
BinaryTree<T>* BinaryTree<T>::DetachRight ()
{
	if (IsEmpty ())
	{
		throw domain_error ("invalid operation");
	}
    BinaryTree* result = right;
    right = new BinaryTree;
    return result;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::Subtree (unsigned int i)
{
	if (i > 1)
	{
		throw domain_error ("parameter error!");
	}
	
	if (IsEmpty ())
	{
		throw domain_error ("invalid operation");
	}

    return (i == 0 ? *left : *right);

}

template <class T>
BinaryTree<T>::BinaryTree() :
    left (0),
    right (0)
{
	;
}

template <class T>
BinaryTree<T>::BinaryTree (T key) :
    key (key),
    left (new BinaryTree ()),
    right (new BinaryTree ())
{
	;
}

template <class T>
void BinaryTree<T>::Purge()
{
    if (!IsEmpty())
    {
		delete left;
		delete right;
		left = 0;
		right = 0;
    }
}

template <class T>
BinaryTree<T>::~BinaryTree()
{ 
    Purge (); 
}

template <class T>
void BinaryTree<T>::DepthFirstTraversal(PrePostVisitor<T>& visitor)
{
    if (visitor.IsDone())
		return;

    if (!IsEmpty ())
    {
		visitor.PreVisit(key);
        left->DepthFirstTraversal(visitor);

		visitor.Visit(key);

		right->DepthFirstTraversal (visitor);
		visitor.PostVisit(key);
    }
}

template <class T>
int BinaryTree<T>::CompareTo(BinaryTree<T>& tree)
{
    if (IsEmpty())
	    return tree.IsEmpty() ? 0 : -1;
    else if (tree.IsEmpty ())
	    return 1;
 
    int result;
    if (key == tree.Key())
    {
        result = 0;
    } 
    else if (key < tree.Key())
    {
        result = -1;
    }
    else
    {
        result = 1;
    }

    if (result == 0)
        result = Left().CompareTo(tree.Left()); 

    if (result == 0)
        result = Right().CompareTo(tree.Right());

    return result;  
}

template <class T>
class BinarySearchTree : public BinaryTree<T>
{
    virtual T* FindMin () = 0;
    virtual T* FindMax () = 0;
    //原SearchableContainer的成员函数。
    virtual bool IsMember (T) = 0;
    virtual void Insert (T) = 0;
    virtual void Withdraw (T) = 0;
    virtual T* Find (T) = 0;
};

#endif //_BINARYTREE_H_
