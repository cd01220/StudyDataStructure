#include "ChainedScatterTable.h"

ChainedScatterTable::Entry::Entry () :
    object (0),
    next (null)
    {}

ChainedScatterTable::ChainedScatterTable (unsigned int _length) :
    HashTable (_length),
    array (_length)
{}

ChainedScatterTable::~ChainedScatterTable()
{}

bool ChainedScatterTable::IsMember (Object const& object) const
{
    for (unsigned int probe = H (object);
	    probe != Entry::null; probe = array [probe].next)
    {
	if (&object == array [probe].object)
	    return true;
    }
    return false;
}

bool ChainedScatterTable::IsFull () const
{
    return (count == length);
}

void ChainedScatterTable::Purge ()
{
    for (unsigned int i = 0; i < length; ++i)
    {
	    if (array [i].object != 0)
	    {
	        if (IsOwner ())
		    delete array [i].object;
	        array [i] = Entry ();
	    }
    }
    count = 0;
}

//added by liuhao 2005-11-19
void ChainedScatterTable::Accept(Visitor& visitor) const
{
    for (unsigned int i = 0; i < length; ++i)
    {
        if(array [i].object != 0)
        {            
			visitor.Visit(*array [i].object);
        }
    }
}

Iterator& ChainedScatterTable::NewIterator() const
{
    Iter *it = new Iter(*this);
	return *it;
}

int ChainedScatterTable::CompareTo (Object const& obj) const
{
    return Container::CompareTo(obj);

    ChainedScatterTable const& arg = dynamic_cast<ChainedScatterTable const&> (obj);

    for(unsigned int i = 0; i < length; ++i)
    {
        if(array[i].object == 0)
        {
            continue;
        }

        if(arg.Find(*array[i].object).IsNull())
        {
            return 1;
        }
    }

    if(count < arg.count)
    {
        return -1;
    }

    return 0;
}

void ChainedScatterTable::Insert (Object& object)
{
    //begin: added by liuhao for 保证链式分散表内不能重复的元素。
    if(!Find(object).IsNull())
    {
        throw invalid_argument ("object has existed");
    }
    //end: added by liuhao for 保证链式分散表内不能重复的元素。

    if (count == length)
	    throw domain_error ("scatter table is full");
    unsigned int probe = H (object);
    if (array [probe].object != 0)
    {
	    while (array [probe].next != Entry::null)
	        probe = array [probe].next;
	    unsigned int const tail = probe;
	    probe = (probe + 1) % length;
	    while (array [probe].object != 0)
	        probe = (probe + 1) % length;
	    array [tail].next = probe;
    }
    array [probe].object = &object;
    array [probe].next = Entry::null;
    ++count;
}

Object& ChainedScatterTable::Find (Object const& object) const
{    
    for (unsigned int probe = H (object);
	    probe != Entry::null && array [probe].object != 0; //随书代码有误，修改之。
        probe = array [probe].next)
    {
	    if (object == *array [probe].object)
	        return *array [probe].object;
    }
    return NullObject::Instance ();
}

void ChainedScatterTable::Withdraw (Object& object)
{
    if (count == 0)
	    throw domain_error ("scatter table is empty");

    unsigned int i = H (object);
    while (i != Entry::null && array [i].object != &object) 
    {
	    i = array[i].next;
    }

    if (i == Entry::null) 
    {
	    throw invalid_argument ("object not found");
    }

    for (;;)
    {
	    unsigned int j;
	    for (j = array [i].next;
	        j != Entry::null; 
            j = array [j].next)
	    {
	        unsigned int const h = H (*array [j].object);
	        bool contained = false;
	        for (unsigned int k = array [i].next;
		         k != array [j].next && !contained;
		         k = array [k].next)
	        {
		        if (k == h)
		            contained = true;
	        }
	        if (!contained)
		        break;
	    }
	    if (j == Entry::null)
	        break;
	    array [i].object = array [j].object;
	    i = j;
    }
    array [i].object = 0;
    array [i].next = Entry::null;
    for (unsigned int j = (i + length - 1U) % length;
	    j != i; j = (j + length - 1U) % length)
    {
	    if (array [j].next == i)
	    {
	        array [j].next = Entry::null;
	        break;
	    }
    }
    --count;
}

//////////////////////////////////////////////////////////////////////////////
//	class ChainedScatterTable::Iter
//////////////////////////////////////////////////////////////////////////////
ChainedScatterTable::Iter::Iter (ChainedScatterTable const& _hashTable) :
    hashTable (_hashTable)
{ 
    Reset (); 
}

bool ChainedScatterTable::Iter::IsDone () const
{ 
    return offset >= hashTable.length;
}

Object& ChainedScatterTable::Iter::operator * () const
{
    if (offset < hashTable.length)
        return *hashTable.array [offset].object;
    else
		return NullObject::Instance ();
}

void ChainedScatterTable::Iter::operator ++ ()
{
    if(offset < hashTable.length)
    {
        ++offset;
    }

    while( offset < hashTable.length && hashTable.array[offset].object == 0)
    {
        ++offset;
    }
}

void ChainedScatterTable::Iter::Reset ()
{ 
    offset = 0;
    while( offset < hashTable.length && hashTable.array[offset].object == 0)
    {
        ++offset;
    }
}