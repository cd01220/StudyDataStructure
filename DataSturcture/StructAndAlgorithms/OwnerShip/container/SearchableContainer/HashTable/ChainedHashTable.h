#ifndef _CHAINED_HASH_TABLE_H_
#define _CHAINED_HASH_TABLE_H

#include "HashTable.h"                 //HashTable基类
#include ".\StructAndAlgorithms\Iterator\Iterator.h"
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h"  //Array模板类
#include ".\StructAndAlgorithms\Array_LinkedList\LinkedList.h" //LinkedList模板类


//////////////////////////////////////////////////////////////////////////////
//	Class: ChainedHashTable
//////////////////////////////////////////////////////////////////////////////
class ChainedHashTable : public HashTable
{
    class Iter;
    Array<LinkedList<Object*> > array;
public:
    ChainedHashTable (unsigned int);
	~ChainedHashTable();

    //class SearchableContainer    
    virtual bool IsMember (Object const&) const;
    virtual void Insert (Object&);
    virtual void Withdraw (Object&);
    virtual Object& Find (Object const&) const;

    //Container class members.
	virtual void Purge();
	virtual void Accept(Visitor&) const;
	virtual Iterator& NewIterator() const;

    //Object class members.
    int CompareTo (Object const&) const;
};

//added by liuhao 2005-11-13
class ChainedHashTable::Iter : public Iterator
{
    ChainedHashTable const& hashTable;
    unsigned int arrayPos;
    ListElement<Object*> const* listElementPos;
public:
    Iter (ChainedHashTable const&);
	bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();
};

#endif //_CHAINED_HASH_TABLE_H