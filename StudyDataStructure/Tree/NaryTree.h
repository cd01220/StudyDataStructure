#ifndef _NARY_TREE_H_
#define _NARY_TREE_H_

#include "Tree.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: NaryTree
//////////////////////////////////////////////////////////////////////////////
template <class T>
class NaryTree : public Tree<T>
{
protected:
    T key;
    size_t const degree;
    vector<NaryTree*> subtree;
public:
    NaryTree(unsigned int);
    NaryTree(unsigned int, T);
    ~NaryTree ();

    T& Key();
	//modefied start at 2005-3-31 按照书上的源代码，不能通过编译
	//  因为基类的虚函数没有被定义。
	NaryTree& Subtree(unsigned int);
	//modefied start at 2005-3-31 
    virtual void AttachKey(T&);
    virtual void DetachKey();
    virtual void AttachSubtree(unsigned int, NaryTree*);
    virtual void DetachSubtree(unsigned int);

	//基类的虚函数。
    bool IsEmpty ();
    bool IsLeaf ();
	void Purge ();
	unsigned int Degree ();
};

template <class T>
bool NaryTree<T>::IsLeaf ()
{	
	if(IsEmpty())
    {   
        //根据定义，空树不是叶节点。
		return false;
    }

    //当前节点的所有子节点如果都是空树，则当前节点为叶子节点。
	for(unsigned int i = 0; i < degree;i++)
	{
        NaryTree &tree = Subtree(i);
        if(!IsEmpty())
        {
            return false;
        }		
	}
	return true;
}

template <class T>
void NaryTree<T>::Purge()
{
	if(IsEmpty())
	{
		return;
	}

    for(unsigned int i = 0; i < degree; ++i)
	{
		delete subtree[i];
	}		
}

template <class T>
NaryTree<T>::~NaryTree()
{
	Purge ();
	return;
}

template <class T>
unsigned int NaryTree<T>::Degree()
{
	return degree;
}


template <class T>
NaryTree<T>::NaryTree(unsigned int _degree): 
    key(0), 
    degree(_degree), 
    subtree(0)
{
}

template <class T>
NaryTree<T>::NaryTree(unsigned int _degree, T _key):
    key(_key),
    degree(_degree),
    subtree(_degree)
{
    for (unsigned int i = 0; i < degree; ++i)
    {
	    subtree [i] = new NaryTree(degree);
    }
}

template <class T>
bool NaryTree<T>::IsEmpty ()
{ 
	return subtree.size() == 0; 
}

template <class T>
T& NaryTree<T>::Key()
{
    if (IsEmpty())
	    throw domain_error ("invalid operation");

    return key;
}

template <class T>
void NaryTree<T>::AttachKey(T& _key)
{
    if (!IsEmpty ())
		throw domain_error ("invalid operation");

    key = _key;
    subtree.resize(degree);
    for (unsigned int i = 0; i < degree; ++i)
    {
	    subtree[i] = new NaryTree(degree);
    }
}

template <class T>
void NaryTree<T>::DetachKey()
{
    if (!IsLeaf ())
	    throw domain_error ("invalid operation");

    for (unsigned int i = 0; i < degree; ++i)
    {
	    delete subtree[i];
    }
    subtree.resize(0);
}

template <class T>
NaryTree<T>& NaryTree<T>::Subtree(unsigned int i)
{
    if (IsEmpty ())
		throw domain_error ("invalid operation");

    return *subtree[i];
}

template <class T>
void NaryTree<T>::AttachSubtree (unsigned int i, NaryTree* tree)
{
    if (IsEmpty ())
		throw domain_error ("invalid operation");

    if (!subtree[i]->IsEmpty())
		throw domain_error ("non-empty subtree present");

    delete subtree[i];
    subtree[i] = tree;
}

template <class T>
void NaryTree<T>::DetachSubtree(unsigned int i)
{
    if (IsEmpty ())
		{throw domain_error ("invalid operation");}

    delete subtree[i];
    subtree[i] = new NaryTree(degree);    
}

#endif //_NARY_TREE_H_