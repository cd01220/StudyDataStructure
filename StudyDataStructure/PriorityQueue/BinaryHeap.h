#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include "Visitor/PureVisitor.h"
#include "PriorityQueue.h"

template<class T>
class BinaryHeap : public PriorityQueue<T>
{
private:
    vector<T> array;

public:
    BinaryHeap(unsigned int);
    ~BinaryHeap();

    //added by liuhao 2005-12-09
    //class PriorityQueue member function.
    virtual void Enqueue(T);
    virtual T& FindMin();
    virtual T DequeueMin();
    //class Container member function.
    virtual void Purge();
    virtual void Accept(Visitor<T>&);
};

template<class T>
BinaryHeap<T>::BinaryHeap (unsigned int length) : 
    array(length + 1)  //array[0] is not used.
{}

template<class T>
void BinaryHeap<T>::Purge ()
{
    count = 0;
}

template<class T>
void BinaryHeap<T>::Accept(Visitor<T>& visitor)
{
    for (unsigned int i = 1; i < count + 1; ++i)
        visitor.Visit(array[i]);
}

template<class T>
BinaryHeap<T>::~BinaryHeap ()
{ 
    Purge(); 
}

template<class T>
void BinaryHeap<T>::Enqueue(T object)
{
    if (count == array.size())
        throw domain_error ("priority queue is full");
    ++count;
    unsigned int i = count;   //i, 当前节点要插入的位置。
    while (i > 1 && array[i / 2] > object)
    {
        array[i] = array[i / 2];
        i = i / 2;
    }
    array[i] = object;
}

template<class T>
T& BinaryHeap<T>::FindMin()
{
    if (count == 0)
        throw domain_error ("priority queue is empty");
    return array[1];
}

template<class T>
T BinaryHeap<T>::DequeueMin ()
{
    if (count == 0)
        throw domain_error ("priority queue is empty");
    T& result = array[1];
    T& last = array[count];
    --count;
    unsigned int i = 1;
    while (2 * i < count + 1)
    {
        unsigned int child = 2 * i;
        if (child + 1 < count + 1 && array[child + 1] < array[child])
            child += 1;
        if (last <= array[child])
            break;
        array[i] = array[child];
        i = child;
    }
    array[i] = last;
    return result;
}


#endif
