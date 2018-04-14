//#include <typeinfo>
#include "HashTable.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: HashTable
//////////////////////////////////////////////////////////////////////////////
HashTable::HashTable (unsigned int _length) :
    length (_length)
{}

unsigned int HashTable::H (Object const& object) const
{ 
    return object.Hash () % length; 
}

