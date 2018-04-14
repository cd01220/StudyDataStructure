#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "..\PureSearchableContainer.h"   //SearchableContainer»ùÀà

//////////////////////////////////////////////////////////////////////////////
//	Class: HashTable
//////////////////////////////////////////////////////////////////////////////
class HashTable : public virtual SearchableContainer
{
protected:
    unsigned int length;
public:
    HashTable (unsigned int);
    virtual unsigned int H (Object const&) const;
};


#endif _HASHTABLE_H_