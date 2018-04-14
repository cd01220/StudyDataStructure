#ifndef _STACK_AS_ARRAY_H_
#define _STACK_AS_ARRAY_H_

#include "..\..\..\Array_LinkedList\Array.h"  //Array模板类。
#include ".\StructAndAlgorithms\Iterator\Iterator.h"  //StackAsArray::Iter基类
#include ".\Stack.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: StackAsArray
//////////////////////////////////////////////////////////////////////////////
class StackAsArray : public Stack
{
    Array<Object*> array;

    class Iter;
public:
    StackAsArray (unsigned int);
    ~StackAsArray();
	void Push (Object&);
    Object& Pop ();
	Object& Top() const;

	virtual void Purge();
	virtual void Accept(Visitor&) const;
	virtual Iterator& NewIterator() const;

    friend class Iter;
};

class StackAsArray::Iter : public Iterator
{
    StackAsArray const& stack;
    unsigned int position;
public:
    Iter (StackAsArray const&);
	bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();
};

#endif  //_STACK_AS_ARRAY_H_