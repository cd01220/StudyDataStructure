#ifndef _BINOMIAL_QUEUE_H_
#define _BINOMIAL_QUEUE_H_

#include ".\PriorityQueue.h"
#include ".\BinomialTree.h"
#include ".\StructAndAlgorithms\Array_LinkedList\LinkedList.h"

class BinomialQueue : public MergeablePriorityQueue
{
    LinkedList<BinomialTree*> list;

    BinomialTree& FindMinTree () const;
    void AddTree (BinomialTree&);
    void RemoveTree (BinomialTree&);

    static BinomialTree* Sum (BinomialTree*, BinomialTree*, BinomialTree*);
    static BinomialTree* Carry (BinomialTree*, BinomialTree*, BinomialTree*);
public:
    BinomialQueue ();
    ~BinomialQueue ();
    // added by liuhao 2005-12-11
    Object& FindMin () const;
    void Merge (MergeablePriorityQueue&);
    void Enqueue (Object&);
    Object& DequeueMin ();

    // added by liuhao 2005-12-11,class Container member function.
    virtual void Purge ();
    virtual void Accept (Visitor&) const;
};


#endif