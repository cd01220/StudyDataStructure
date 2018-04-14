#include ".\QueueAsArray.h"

QueueAsArray::QueueAsArray (unsigned int size) :
    array (size),
    head (0),
    tail (size - 1U)
    {}

void QueueAsArray::Accept (Visitor& visitor) const
{
    for (unsigned int i = 0;
		i < count && !visitor.IsDone (); ++i)
    {
	    visitor.Visit (*array [i]);
    }
}

void QueueAsArray::Purge ()
{
    if (IsOwner ())
    {
	    for (unsigned int i = 0; i < count; ++i)
	    {
	        delete array [head];
	        if (++head == array.Length ())
            {
		        head = 0;
            }
	    }
    }
    count = 0;
}

QueueAsArray::~QueueAsArray ()
{ 
    Purge (); 
}

Object& QueueAsArray::Head () const
{
    if (count == 0)
	    throw domain_error ("queue is empty");
    return *array [head];
}

void QueueAsArray::Enqueue (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("queue is full");
    if (++tail == array.Length ())
	tail = 0;
    array [tail] = &object;
    ++count;
}

Object& QueueAsArray::Dequeue ()
{
    if (count == 0)
    {
	    throw domain_error ("queue is empty");
    }
    Object& result = *array [head];
    if (++head == array.Length ())
    {
	    head = 0;
    }
    --count;
    return result;
}

Iterator& QueueAsArray::NewIterator() const
{
	Iter *it = new Iter(*this);
	return *it;
}

QueueAsArray::Iter::Iter (QueueAsArray const& _queue) :
    queue (_queue)
{ 
    Reset ();
}

bool QueueAsArray::Iter::IsDone () const
{ 
    return position >= queue.count;
}

Object& QueueAsArray::Iter::operator * () const
{
    if (position < queue.count)
		return *queue.array [position];
    else
		return NullObject::Instance ();
}

void QueueAsArray::Iter::operator ++ ()
{
    if (position < queue.count)
    {
	    ++position;
    }
}

void QueueAsArray::Iter::Reset ()
{ 
    position = 0; 
}

