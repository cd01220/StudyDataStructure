#ifndef _LEFTIST_HEAP_H_
#define _LEFTIST_HEAP_H_

#include "PriorityQueue.h"    //class MergeablePriorityQueue 基类定义。
#include "Tree/BinaryTree.h"

template<class T>
class BinaryMergeablePriorityQueue : public BinaryTree<T>
{
public:
    BinaryMergeablePriorityQueue() : BinaryTree(){}
    BinaryMergeablePriorityQueue(T& object) : BinaryTree(object){}
    //class PriorityQueue member function.
    virtual void Enqueue(T) = 0;
    virtual T& FindMin() = 0;
    virtual T DequeueMin() = 0;

    //class MergeablePriorityQueue member function.
    virtual void Merge(BinaryMergeablePriorityQueue<T>&) = 0;
};

template<class T>
class LeftistHeap : public BinaryMergeablePriorityQueue<T>
{
    unsigned int nullPathLength;

    void SwapContents(LeftistHeap&);
public:
    LeftistHeap();
    LeftistHeap(T);

    LeftistHeap<T>& Left();
    LeftistHeap<T>& Right();
    void Merge(BinaryMergeablePriorityQueue&); 

    void Enqueue(T);
    T& FindMin();
    T DequeueMin();
};

template<class T>
LeftistHeap<T>::LeftistHeap() : nullPathLength(0)
{
}

template<class T>
LeftistHeap<T>::LeftistHeap(T object) : nullPathLength(1)
{
    key = object;
    left = new LeftistHeap();
    right = new LeftistHeap();
}

template<class T>
void LeftistHeap<T>::SwapContents(LeftistHeap<T>& heap)
{
    std::swap(nullPathLength, heap.nullPathLength);
    std::swap(key, heap.key);
    std::swap(left, heap.left);
    std::swap(right, heap.right);
}

template<class T>
LeftistHeap<T>& LeftistHeap<T>::Left()
{
    return dynamic_cast<LeftistHeap<T>&>(BinaryTree::Left());
}

template<class T>
LeftistHeap<T>& LeftistHeap<T>::Right()
{
    return dynamic_cast<LeftistHeap<T>&>(BinaryTree::Right());
}

template<class T>
void LeftistHeap<T>::Merge(BinaryMergeablePriorityQueue<T>& queue)
{
    LeftistHeap<T>& arg = dynamic_cast<LeftistHeap<T>&>(queue);
    if (IsEmpty ())
    {    
        SwapContents (arg);
    }
    else if (!arg.IsEmpty())
    {
        if (key > arg.key)
            SwapContents (arg);
        Right().Merge (arg);
        if (Left().nullPathLength < Right().nullPathLength)
            std::swap (left, right);
        nullPathLength = 1 + std::min (Left().nullPathLength,
            Right().nullPathLength);
    }
}

template<class T>
void LeftistHeap<T>::Enqueue(T object)
{
    LeftistHeap<T> heap(object);
    Merge(heap);
}

template<class T>
T& LeftistHeap<T>::FindMin()
{
    if (IsEmpty())
        throw domain_error ("priority queue is empty");
    return key;
}

template<class T>
T LeftistHeap<T>::DequeueMin()
{
    if (IsEmpty())
        throw domain_error ("priority queue is empty");
    T result = key;
    LeftistHeap<T>& oldLeft = Left();
    LeftistHeap<T>& oldRight = Right();
    key = 0;
    left = 0;
    right = 0;
    SwapContents(oldLeft);
    delete &oldLeft;
    Merge(oldRight);
    delete &oldRight;
    return result;
}

#endif