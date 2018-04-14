#include ".\QueueAsLinkedList.h"

QueueAsLinkedList::QueueAsLinkedList () :
    list ()
    {}

void QueueAsLinkedList::Purge ()
{
    if (IsOwner ())
    {
	    ListElement<Object*> const* ptr;

	    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	        delete ptr->Datum ();
    }
    list.Purge ();
    count = 0;
}

QueueAsLinkedList::~QueueAsLinkedList ()
    { Purge (); }

Object& QueueAsLinkedList::Head () const
{
    if (count == 0)
	throw domain_error ("queue is empty");
    return *list.First ();
}

void QueueAsLinkedList::Enqueue (Object& object)
{
    list.Append (&object);
    ++count;
}

Object& QueueAsLinkedList::Dequeue ()
{
    if (count == 0)
	throw domain_error ("queue is empty");
    Object& result = *list.First ();
    list.Extract (&result);
    --count;
    return result;
}

void QueueAsLinkedList::Accept (Visitor& visitor) const
{
	ListElement<Object*> const* ptr;

    for (ptr = list.Head ();
	    ptr != 0 && !visitor.IsDone (); ptr = ptr->Next ())
    {
	    visitor.Visit (*ptr->Datum ());
    }
}


Iterator& QueueAsLinkedList::NewIterator() const
{
	return *new Iter(*this);
}

QueueAsLinkedList::Iter::Iter (
    QueueAsLinkedList const& _queue) :
    queue (_queue)
{ 
    Reset (); 
}

bool QueueAsLinkedList::Iter::IsDone () const
    { return position == 0; }

Object& QueueAsLinkedList::Iter::operator * () const
{
    if (position != 0)
	    return *position->Datum ();
    else
	    return NullObject::Instance ();
}

void QueueAsLinkedList::Iter::operator ++ ()
{
    if (position != 0)
	    position = position->Next ();
}

void QueueAsLinkedList::Iter::Reset ()
    { position = queue.list.Head(); }
