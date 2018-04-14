#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include ".\StructAndAlgorithms\OwnerShip\container\PureContainer.h"

class PriorityQueue : public virtual Container
{
public:
    virtual void Enqueue (Object&) = 0;
    virtual Object& FindMin () const = 0;
    virtual Object& DequeueMin () = 0;
};

class MergeablePriorityQueue : public virtual PriorityQueue
{
public:
    virtual void Merge (MergeablePriorityQueue&) = 0;
};

#endif