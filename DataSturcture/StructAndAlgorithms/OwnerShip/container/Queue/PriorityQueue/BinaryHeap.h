#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include ".\PriorityQueue.h"
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h"

class BinaryHeap : public PriorityQueue
{
    Array<Object*> array;
public:
    BinaryHeap (unsigned int);
    ~BinaryHeap ();
    //added by liuhao 2005-12-09
    //class PriorityQueue member function.
    virtual void Enqueue (Object&); 
    virtual Object& FindMin () const;
    virtual Object& DequeueMin ();
    //class Container member function.
    virtual void Purge ();
    virtual void Accept (Visitor&) const;
};

#endif