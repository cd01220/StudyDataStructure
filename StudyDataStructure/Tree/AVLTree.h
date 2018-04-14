#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include ".\BST.h"
//////////////////////////////////////////////////////////////////////////////
//	class AVLTree
//////////////////////////////////////////////////////////////////////////////
template <class T>
class AVLTree : public BST<T>
{
protected:
    int height;

    int BalanceFactor() ;
    void AdjustHeight();
    void LLRotation();
    void LRRotation();
    void RRRotation();
    void RLRotation();
    void AttachKey(T&);
    void DetachKey();
    void Balance();
public:
    AVLTree();

    int Height();
    AVLTree& Left();
    AVLTree& Right();
};

template <class T>
AVLTree<T>& AVLTree<T>::Left ()
{
    return dynamic_cast<AVLTree&>(BST::Left());
}

template <class T>
AVLTree<T>& AVLTree<T>::Right() 
{
    return dynamic_cast<AVLTree&>(BST::Right());
}

template <class T>
AVLTree<T>::AVLTree() :
    BST(),
    height(-1)
{}

template <class T>
int AVLTree<T>::Height() 
{ 
    return height; 
}

template <class T>
void AVLTree<T>::AdjustHeight()
{
    if (IsEmpty())
        height = -1;
    else
        height = std::max(left->Height(), right->Height()) + 1;
}

template <class T>
int AVLTree<T>::BalanceFactor()
{
    if (IsEmpty())
        return 0;
    else
        return left->Height() - right->Height();
}

template <class T>
void AVLTree<T>::RRRotation()
{
    if (IsEmpty())
        throw domain_error("invalid rotation");
    BinaryTree<T>* const tmp = left;
    left = right;
    right = Left().right;
    Left().right = Left().left;
    Left().left = tmp;

    T tmpObj = key;
    key = Left().key;
    Left().key = tmpObj;

    Left().AdjustHeight();
    AdjustHeight();
}

template <class T>
void AVLTree<T>::LLRotation()
{
    if (IsEmpty())
        throw domain_error ("invalid rotation");
    BinaryTree* const tmp = right;
    right = left;
    left = Right().left;
    Right().left = Right().right;
    Right().right = tmp;

    T tmpObj = key;
    key = Right().key;
    Right().key = tmpObj;

    Right().AdjustHeight();
    AdjustHeight ();
}

template <class T>
void AVLTree<T>::LRRotation()
{
    if (IsEmpty ())
        throw domain_error ("invalid rotation");
    Left ().RRRotation ();
    LLRotation ();
}

template <class T>
void AVLTree<T>::RLRotation()
{
    if(IsEmpty())
        throw domain_error ("invalid rotation");
    Right().LLRotation();
    RRRotation();
}

template <class T>
void AVLTree<T>::Balance ()
{
    AdjustHeight();
    if (std::abs(BalanceFactor()) > 1)
    {
        if (BalanceFactor() > 0)
        {
            if (Left().BalanceFactor() > 0)
                LLRotation();
            else
                LRRotation();
        }
        else
        {
            if (Right().BalanceFactor() < 0)
                RRRotation();
            else
                RLRotation();
        }
    }
}

template <class T>
void AVLTree<T>::AttachKey(T& tKey)
{
    if (!IsEmpty ())
        throw domain_error("invalid operation");
    key = tKey;
    left = new AVLTree();
    right = new AVLTree();
    height = 0;
}

template <class T>
void AVLTree<T>::DetachKey()
{
    height = -1;
    BST::DetachKey();
}

#endif