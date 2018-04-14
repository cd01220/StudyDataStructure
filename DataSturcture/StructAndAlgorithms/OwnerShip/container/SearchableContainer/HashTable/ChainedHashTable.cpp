#include "ChainedHashTable.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: ChainedHashTable
//////////////////////////////////////////////////////////////////////////////
ChainedHashTable::ChainedHashTable (unsigned int _length) :
    HashTable (_length),
    array (_length)
    {}

ChainedHashTable::~ChainedHashTable ()
    { Purge (); }

void ChainedHashTable::Purge ()
{
    for (unsigned int i = 0; i < length; ++i)
    {
		if (IsOwner ())
		{
			ListElement<Object*> const* ptr;

			for (ptr = array [i].Head (); ptr != 0; ptr = ptr->Next ())
            {
			    delete ptr->Datum ();
            }
		}
		array [i].Purge ();
    }
    count = 0;
}

//added by liuhao 2005-11-12
void ChainedHashTable::Accept (Visitor& visitor) const
{
    for (unsigned int i = 0; i < length; ++i)
    {
		ListElement<Object*> const* ptr;

		for (ptr = array [i].Head ();
			ptr != 0 && !visitor.IsDone(); ptr = ptr->Next ())
        {
            
			visitor.Visit(*ptr->Datum ());
        }
    }
	return;
}

//added by liuhao 2005-11-12
Iterator& ChainedHashTable::NewIterator() const
{
    Iter *it = new Iter(*this);
	return *it;
}

bool ChainedHashTable::IsMember (Object const& object) const
{
	ListElement<Object*> const* ptr;
	for (ptr = array [H (object)].Head (); ptr != 0; ptr = ptr->Next())
    {
		if (&object == ptr->Datum ())
			return true;
    }
	return false;
}

void ChainedHashTable::Insert (Object& object)
{
	int a = H (object);
    array [H (object)].Append (&object);
    ++count;
}

void ChainedHashTable::Withdraw (Object& object)
{
    array [H (object)].Extract (&object);
    --count;
}

Object& ChainedHashTable::Find (Object const& object) const
{
    ListElement<Object*> const* ptr;

    for (ptr = array [H (object)].Head (); ptr != 0; ptr = ptr->Next())
    {
	    if (object == *ptr->Datum ())
	        return *ptr->Datum ();
    }
    return NullObject::Instance ();
}

//class ChainedHashTable::Iter member func, added by liuhao
ChainedHashTable::Iter::Iter (ChainedHashTable const&arg) :
    hashTable(arg)
{
    Reset();
}

bool ChainedHashTable::Iter::IsDone () const
{
    //IsDone()返回true的条件为数组遍历了到最后，
    //且数组中的LinkedList了遍历完成。
    return listElementPos == 0; 
}

void ChainedHashTable::Iter::Reset ()
{
    arrayPos = 0;
    listElementPos = hashTable.array[arrayPos].Head();
    if(listElementPos == 0)
    {
        operator++();
    }
}

Object& ChainedHashTable::Iter::operator * () const
{
    if(0 == listElementPos)
    {
        throw out_of_range ("ChainedHashTable::Iter out of range!");
    }

    return *listElementPos->Datum();
}

void ChainedHashTable::Iter::operator ++ ()
{
    if(listElementPos != 0)
    {
        listElementPos = listElementPos->Next();
    }

    while(listElementPos == 0 && ++arrayPos < hashTable.length)
    {
        listElementPos = hashTable.array[arrayPos].Head();
    }   
}

int ChainedHashTable::CompareTo (Object const& object) const
{
   return Container::CompareTo(object);
}
