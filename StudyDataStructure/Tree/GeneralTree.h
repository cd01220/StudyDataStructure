#ifndef _GENERALTREE_H_
#define _GENERALTREE_H_

#include "Tree.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: GeneralTree
//////////////////////////////////////////////////////////////////////////////
template <class T>
class GeneralTree: public Tree<T>
{
protected:
    T key;
    size_t degree;
    list<GeneralTree*> subTreeList;
public:
    GeneralTree (T);
    ~GeneralTree ();

    //Tree class members.
    T& Key();
    GeneralTree& Subtree(unsigned int);
    bool IsEmpty();
    bool IsLeaf();
    unsigned int Degree();
    int Height();
    unsigned int Count();

    virtual void AttachSubtree(GeneralTree*);
    virtual void DetachSubtree(GeneralTree*);
    
private:
    void Purge();
};

template <class T>
GeneralTree<T>::GeneralTree(T key) : key(key), degree(0)
{
}

template <class T>
GeneralTree<T>::~GeneralTree()
{ 
    Purge(); 
}

template <class T>
void GeneralTree<T>::Purge()
{
    list<GeneralTree*>::iterator iter;
    for (iter = subTreeList.begin(); iter != subTreeList.end(); ++iter)
	    delete *iter;

    subTreeList.clear();
}

template <class T>
int GeneralTree<T>::Height()
{
    //根据定义空树的高度为-1(注：广义树没有空树,因此广义树必须重载本函数。);
    int iMaxSubHeight = 0;
    for (unsigned int i = 0; i < Degree (); ++i)
    {
        iMaxSubHeight = std::max(iMaxSubHeight, Subtree(i).Height() + 1);
    }

    return iMaxSubHeight;
}

template <class T>
unsigned int GeneralTree<T>::Count()
{
    unsigned int ret = 1;
    for (unsigned int i = 0; i < Degree(); ++i)
    {
        ret += Subtree(i).Count();
    }

    return ret;
}

//added by liuhao 205-11-19, 根据定义，广义树没有空树。
template <class T>
bool GeneralTree<T>::IsEmpty()
{
    return false;
}

template <class T>
bool GeneralTree<T>::IsLeaf()
{
    return (degree == 0);
}

template <class T>
unsigned int GeneralTree<T>::Degree()
{
    return degree;
}

template <class T>
T& GeneralTree<T>::Key()
{ 
    return key; 
}

template <class T>
GeneralTree<T>& GeneralTree<T>::Subtree(unsigned int index)
{
    if (index >= degree)
	    throw out_of_range ("invalid subtree index");

    list<GeneralTree*>::iterator iter = subTreeList.begin();
    unsigned int i;
    for (i = 0; i < index; ++i)
    {
        ++iter;
    }

    GeneralTree* tree = *iter;
    return *tree;
}

template <class T>
void GeneralTree<T>::AttachSubtree(GeneralTree* tree)
{
    subTreeList.push_back(tree);
    ++degree;
}

template <class T>
void GeneralTree<T>::DetachSubtree(GeneralTree* tree)
{
    subTreeList.remove(tree);
    --degree;
}

#endif  //_GENERALTREE_H_