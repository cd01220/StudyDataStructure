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

class BinaryHeap : public PriorityQueue
{
    Array<Object*> array;
public:
    BinaryHeap (unsigned int);
    ~BinaryHeap ();
    // ...
};

BinaryHeap::BinaryHeap (unsigned int length) :
    array (length, 1)
    {}

void BinaryHeap::Purge ()
{
    if (IsOwner ())
    {
	for (unsigned int i = 1; i < count + 1; ++i)
	    delete array [i];
    }
    count = 0;
}

BinaryHeap::~BinaryHeap ()
    { Purge (); }


void BinaryHeap::Enqueue (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("priority queue is full");
    ++count;
    unsigned int i = count;
    while (i > 1 && *array [i / 2] > object)
    {
	array [i] = array [i / 2];
	i /= 2;
    }
    array [i] = &object;
}

Object& BinaryHeap::FindMin () const
{
    if (count == 0)
	throw domain_error ("priority queue is empty");
    return *array [1];
}

Object& BinaryHeap::DequeueMin ()
{
    if (count == 0)
	throw domain_error ("priority queue is empty");
    Object& result = *array [1];
    Object& last = *array [count];
    --count;
    unsigned int i = 1;
    while (2 * i < count + 1)
    {.
	unsigned int child = 2 * i;
	if (child + 1 < count + 1
	    && *array [child + 1] < *array [child])
	    child += 1;
	if (last <= *array [child])
	    break;
	array [i] = array [child];
	i = child;
    }
    array [i] = &last;
    return result;
}

