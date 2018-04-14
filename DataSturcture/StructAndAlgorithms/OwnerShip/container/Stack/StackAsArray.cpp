
#include ".\StackAsArray.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: StackAsArray
//////////////////////////////////////////////////////////////////////////////
StackAsArray::StackAsArray (unsigned int size) :
    array (size)
{}

void StackAsArray::Purge()
{
    if (IsOwner ())
    {
		for (unsigned int i = 0; i < count; ++i)
			delete array [i];
    }
    count = 0;
}

StackAsArray::~StackAsArray ()
{ 
	Purge (); 
}

void StackAsArray::Push (Object& object)
{
    if (count == array.Length ())
    {
		throw domain_error ("stack is full");
    }
    array [count++] = &object;
}

Object& StackAsArray::Pop ()
{
    if (count == 0)
	throw domain_error ("stack is empty");
    return *array [--count];
}

Object& StackAsArray::Top () const
{
    if (count == 0)
	throw domain_error ("stack is empty");
    return *array [count - 1U];
}

void StackAsArray::Accept (Visitor& visitor) const
{
    for (unsigned int i = 0;
		i < count && !visitor.IsDone (); ++i)
    {
	    visitor.Visit (*array [i]);
    }
}

Iterator& StackAsArray::NewIterator() const
{
	Iter *it = new Iter(*this);
	return *it;
}

StackAsArray::Iter::Iter (StackAsArray const& _stack) :
    stack (_stack)
{ 
    Reset (); 
}

bool StackAsArray::Iter::IsDone () const
{ 
    return position >= stack.count; 
}

Object& StackAsArray::Iter::operator * () const
{
    if (position < stack.count)
		return *stack.array [position];
    else
		return NullObject::Instance ();
}

void StackAsArray::Iter::operator ++ ()
{
    if (position < stack.count)
	++position;
}

void StackAsArray::Iter::Reset ()
{ position = 0; }
