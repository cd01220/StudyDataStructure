#include ".\LeftistHeap.h"

LeftistHeap::LeftistHeap () : nullPathLength(0)
{
}

LeftistHeap::LeftistHeap (Object& object) :
    nullPathLength(1)
{
    key = &object;
    left = new LeftistHeap ();
    right = new LeftistHeap ();
}

void LeftistHeap::SwapContents (LeftistHeap& heap)
{
    std::swap(nullPathLength, heap.nullPathLength);
    std::swap(key, heap.key);
    std::swap(left, heap.left);
    std::swap(right, heap.right);
}

LeftistHeap& LeftistHeap::Left () const
{
    return dynamic_cast<LeftistHeap&>(BinaryTree::Left());
}

LeftistHeap& LeftistHeap::Right () const
{
    return dynamic_cast<LeftistHeap&>(BinaryTree::Right());
}

void LeftistHeap::Merge (BinaryMergeablePriorityQueue& queue)
{
    LeftistHeap& arg = dynamic_cast<LeftistHeap&> (queue);
    if (IsEmpty ())
    {    
        SwapContents (arg);
    }
    else if (!arg.IsEmpty ())
    {
	    if (*key > *arg.key)
	        SwapContents (arg);
	    Right ().Merge (arg);
	    if (Left ().nullPathLength < Right ().nullPathLength)
            std::swap (left, right);
        nullPathLength = 1 + std::min (Left ().nullPathLength,
	        Right ().nullPathLength);
    }
}

void LeftistHeap::Enqueue (Object& object)
{
    LeftistHeap heap(object);
    Merge (heap);
}

Object& LeftistHeap::FindMin () const
{
    if (IsEmpty ())
	    throw domain_error ("priority queue is empty");
    return *key;
}

Object& LeftistHeap::DequeueMin ()
{
    if (IsEmpty ())
	    throw domain_error ("priority queue is empty");
    Object& result = *key;
    LeftistHeap& oldLeft = Left ();
    LeftistHeap& oldRight = Right ();
    key = 0;
    left = 0;
    right = 0;
    SwapContents (oldLeft);
    delete &oldLeft;
    Merge (oldRight);
    delete &oldRight;
    return result;
}
