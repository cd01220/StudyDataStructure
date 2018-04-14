#ifndef _BST_H_
#define _BST_H_

#include "BinaryTree.h"
#include "SearchTree.h"

//BST: Binary Sort Tree 或 Binary Search Tree
//修改记录：随书代码导制多继承， 致使SearchTree的子类的Subtree()函数只能返回Tree&,
// 故修改之。
template <class T>
class BST : public BinarySearchTree<T>
{
protected:
    virtual void AttachKey(T&);
    virtual void DetachKey();
    virtual void Balance();
public:
    BST& Left ();
    BST& Right ();
    //added by liuhao.
    virtual ~BST() {}

	//added by liuhao 2005-11-25, 随书代码省略了以下几个函数的申明，但是随书代
    //码包含以下函数的定义。
	T* Find (T);
	T* FindMin ();	
    T* FindMax ();
	void Insert (T);
    void Withdraw (T);
    // added by liuhao.
	bool IsMember (T); //BinarySearchTree成员函数。
    BST<T>& Subtree (unsigned int i);
};

template <class T>
bool BST<T>::IsMember (T key)
{	
    return (*Find(key) == key);
}

template <class T>
BST<T>& BST<T>::Left()
{ 
    return dynamic_cast<BST&>(BinaryTree::Left()); 
}

template <class T>
BST<T>& BST<T>::Right()
{ 
	return dynamic_cast<BST&> (BinaryTree::Right ()); 
}

template <class T>
T* BST<T>::Find(T tKey)
{
    if (IsEmpty ())
    {
        return NULL;
    }

    int const diff = Compare(tKey, key);

    if (diff == 0)
		return &key;
    else if (diff < 0)
		return Left().Find(tKey);
    else
		return Right().Find(tKey);
}

template <class T>
T* BST<T>::FindMin()
{
    if (IsEmpty())
		return NULL;
    else if (Left().IsEmpty())
		return &key;
    else
		return Left().FindMin();
}

template <class T>
T* BST<T>::FindMax()
{
    if (IsEmpty ())
		return NULL;
    else if (Right().IsEmpty ())
		return &key;
    else
		return Right().FindMax();
}

template <class T>
void BST<T>::Insert(T tKey)
{
    if (IsEmpty ())
	    AttachKey(tKey);
    else
    {
		int const diff = Compare(tKey, key);
		if (diff == 0)
			throw invalid_argument ("duplicate key");
		if (diff < 0)
			Left().Insert(tKey);
		else
			Right().Insert(tKey);
    }
    Balance();
}

template <class T>
void BST<T>::AttachKey (T& tKey)
{
    if (!IsEmpty ())
	    throw domain_error ("invalid operation");
    key = tKey;
    left = new BST();
    right = new BST();
}

template <class T>
void BST<T>::Balance ()
{}

template <class T>
void BST<T>::Withdraw (T tKey)
{
    if (IsEmpty ())
	    throw invalid_argument ("object not found");

    int const diff = Compare (tKey, key);
    if (diff == 0)
    {
	    if (!Left().IsEmpty())
	    {
	        T* max = Left().FindMax();
	        key = *max;
	        Left().Withdraw(key);
	    }
	    else if (!Right().IsEmpty())
	    {
	        T* min = Right().FindMin();
	        key = *min;
	        Right().Withdraw (key);
	    }
	    else
	        DetachKey();
    }
    else if (diff < 0)
	    Left().Withdraw(tKey);
    else
	    Right().Withdraw(tKey);

    Balance();
}

template <class T>
void BST<T>::DetachKey ()
{
    if (!IsLeaf ())
        throw domain_error ("invalid operation");

    T& result = key;
    delete left;
    delete right;
    key = 0;
    left = 0;
    right = 0;
}

template <class T>
BST<T>& BST<T>::Subtree(unsigned int i)
{
    return dynamic_cast<BST&>(BinaryTree<T>::Subtree(i));
}

#endif //_BST_H_