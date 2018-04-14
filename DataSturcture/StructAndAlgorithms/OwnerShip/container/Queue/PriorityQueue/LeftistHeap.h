#ifndef _LEFTIST_HEAP_H_
#define _LEFTIST_HEAP_H_

#include ".\PriorityQueue.h"    //class MergeablePriorityQueue 基类定义。
#include ".\StructAndAlgorithms\OwnerShip\container\Tree\BinaryTree.h"

class BinaryMergeablePriorityQueue : public BinaryTree  
{
public:
    BinaryMergeablePriorityQueue() : BinaryTree(){}
    BinaryMergeablePriorityQueue(Object& object) : BinaryTree(object){}
    //class PriorityQueue member function.
    virtual void Enqueue (Object&) = 0;
    virtual Object& FindMin () const = 0;
    virtual Object& DequeueMin () = 0;

    //class MergeablePriorityQueue member function.
    virtual void Merge (BinaryMergeablePriorityQueue&) = 0;
};

//多继承会导致Left()之类的函数不通过编译(返回值类型为子类，且函数定义包括const)，
//故修改之。
//class LeftistHeap :
//    public BinaryTree, public MergeablePriorityQueue
class LeftistHeap : public BinaryMergeablePriorityQueue
{
    unsigned int nullPathLength;

    void SwapContents (LeftistHeap&);
public:
    LeftistHeap ();
    LeftistHeap (Object&);

    LeftistHeap& Left () const;
    LeftistHeap& Right () const;
    void Merge (BinaryMergeablePriorityQueue&); //modefied by liuhao 2005-12-10
    //added by liuhao 2005-12-10
    void Enqueue (Object&);
    Object& FindMin () const;
    Object& DequeueMin ();
};

#endif