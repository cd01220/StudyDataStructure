#include "OrderedList.h"

ListAsArray::ListAsArray (unsigned int size) :
    array (size)
{}

ListAsArray::~ListAsArray()
{
    Purge();
}

void ListAsArray::Purge()
{
    if (IsOwner ())
    {
		for (unsigned int i = 0; i < count; ++i)
			delete array [i];
    }
    count = 0;
}

void ListAsArray::Accept(Visitor& visitor) const
{
	for (unsigned int i = 0;
		i < count && !visitor.IsDone (); ++i)
    {
	    visitor.Visit (*array [i]);
    };
}

void ListAsArray::Insert (Object& object)
{
    if (count == array.Length ())
		throw domain_error ("list is full");
    array [count] = &object;
    ++count;
}

Object& ListAsArray::operator [] (unsigned int offset) const
{
    if (offset >= count)
		throw out_of_range ("invalid offset");
    return *array [offset];
}

Object& ListAsArray::Find (Object const& object) const
{
    for (unsigned int i = 0; i < count; ++i)
	if (*array [i] == object)
	    return *array [i];
    return NullObject::Instance ();
}

bool ListAsArray::IsMember (Object const& object) const
{
    for (unsigned int i = 0; i < count; ++i)
    {
	    if (array [i] == &object)
	        return true;
    }
    return false;
}

void ListAsArray::Withdraw (Object& object)
{
    if (count == 0)
		throw domain_error ("list is empty");

    unsigned int i = 0;
    while (i < count && array [i] != &object)
		++i;

    if (i == count)
		throw invalid_argument ("object not found");

    for ( ; i < count - 1U; ++i)
		array [i] = array [i + 1];

    --count;
}

Position& ListAsArray::FindPosition (Object const& object) const
{
    unsigned int i = 0;
    while (i < count && *array [i] != object)
    {
	    ++i;
    }
    return *new Pos (*this, i);
}

void ListAsArray::Withdraw (Position const& arg)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == 0)
		throw domain_error ("list is empty");

    if (&position.list != this || position.offset >= count)
		throw invalid_argument ("invalid position");

    for (unsigned int i = position.offset; i < count-1U; ++i)
    {
	    array [i] = array [i + 1];
    }
    --count;
}

void ListAsArray::InsertAfter (
    Position const& arg, Object& object)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == array.Length ())
	    throw domain_error ("list is full");
    if (&position.list != this || position.offset >= count)
	    throw invalid_argument ("invalid position");

    unsigned int const insertPosition = position.offset + 1;

    for (unsigned int i = count; i > insertPosition; --i)
    {
	    array [i] = array [i - 1U];
    }
    array [insertPosition] = &object;
    ++count;
}

void ListAsArray::InsertBefore (Position const& arg, Object& object)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == array.Length ())
	    throw domain_error ("list is full");
    if (&position.list != this || position.offset >= count)
	    throw invalid_argument ("invalid position");

    unsigned int const insertPosition = position.offset;

    for (unsigned int i = count; i > insertPosition; --i)
    {
	    array [i] = array [i - 1U];
    }
    array [insertPosition] = &object;
    ++count;
}

Object& ListAsArray::operator [] (Position const& arg) const
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.offset >= count)
		throw invalid_argument ("invalid position");
    return *array [position.offset];
}

Iterator& ListAsArray::NewIterator() const
{
	return *new Pos(*this,0);
}

ListAsArray::Pos::Pos(const ListAsArray& _list,int _offset) : 
    list(_list),
    offset(_offset)
{
}

void ListAsArray::Pos::Reset()
{
	offset = 0;
}

bool ListAsArray::Pos::IsDone () const
{
	return (offset >= list.count);
}

void ListAsArray::Pos::operator ++ ()
{
	if(offset < list.count)
		offset ++;
}

Object& ListAsArray::Pos::operator * () const
{
	if(offset < list.count)	
        return *list.array[offset];
	else
		return NullObject::Instance();
}
