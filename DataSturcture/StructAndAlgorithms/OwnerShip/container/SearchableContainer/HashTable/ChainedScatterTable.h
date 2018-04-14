#ifndef _CHAIN_SCATTER_TABLE_
#define _CHAIN_SCATTER_TABLE_

#include "HashTable.h" //HashTable基类   
#include ".\StructAndAlgorithms\Iterator\Iterator.h"
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h"  //Array模板类

class ChainedScatterTable : public HashTable
{
    class Iter;
    class Entry
    {
        public:
	    enum { null = ~0U };
	    Object* object;
	    unsigned int next;

	    Entry ();
    };

    Array<Entry> array;
public:
    ChainedScatterTable (unsigned int);
    //added by liuhao2005-11-17
    ~ChainedScatterTable();

    //class SearchableContainer
    bool IsMember (Object const&) const;
    void Insert (Object&);
    void Withdraw (Object&);
    Object& Find (Object const&) const;

    //Container class members.
    bool IsFull () const;
	void Purge();
	void Accept(Visitor&) const;
	Iterator& NewIterator() const;

    //Object class members.
    int CompareTo (Object const&) const;
    
};

//added by liuhao 2005-11-19
class ChainedScatterTable::Iter : public Iterator
{
    ChainedScatterTable const& hashTable;
    unsigned int offset;
public:
    Iter (ChainedScatterTable const&);
	bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();
};
#endif //_CHAIN_SCATTER_TABLE_