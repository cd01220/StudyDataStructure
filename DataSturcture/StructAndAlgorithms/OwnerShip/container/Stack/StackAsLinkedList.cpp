#include ".\StackAsLinkedList.h"

//////////////////////////////////////////////////////////////////////////////
//	Class:StackAsLinkedList 
//////////////////////////////////////////////////////////////////////////////
StackAsLinkedList::StackAsLinkedList () :
    list ()
    {}

void StackAsLinkedList::Purge ()
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

StackAsLinkedList::~StackAsLinkedList ()
{
	Purge (); 
}

void StackAsLinkedList::Push (Object& object)
{
    list.Prepend (&object);
    ++count;
}

Object& StackAsLinkedList::Pop ()
{
    if (count == 0)
		throw domain_error ("stack is empty");

    Object& result = *list.First();
    list.Extract (&result);
    --count;
    return result;
}

Object& StackAsLinkedList::Top () const
{
    if (count == 0)
	    throw domain_error ("stack is empty");
    return *list.First ();
}

void StackAsLinkedList::Accept (Visitor& visitor) const
{
    ListElement<Object*> const* ptr;

    for (ptr = list.Head ();
	    ptr != 0 && !visitor.IsDone (); ptr = ptr->Next ())
    {
	    visitor.Visit (*ptr->Datum ());
    }
}

Iterator& StackAsLinkedList::NewIterator() const
{
	return *new Iter(*this);
}

StackAsLinkedList::Iter::Iter (
    StackAsLinkedList const& _stack) :
    stack (_stack)
    { Reset (); }

bool StackAsLinkedList::Iter::IsDone () const
    { return position == 0; }

Object& StackAsLinkedList::Iter::operator * () const
{
    if (position != 0)
	    return *position->Datum ();
    else
	    return NullObject::Instance ();
}

void StackAsLinkedList::Iter::operator ++ ()
{
    if (position != 0)
	    position = position->Next ();
}

void StackAsLinkedList::Iter::Reset ()
    { position = stack.list.Head(); }

