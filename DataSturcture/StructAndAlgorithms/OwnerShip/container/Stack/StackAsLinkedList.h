#ifndef _STACK_AS_LINKEDLIST_H_
#define _STACK_AS_LINKEDLIST_H_

#include ".\Stack.h"
#include ".\StructAndAlgorithms\Iterator\Iterator.h"  //StackAsArray::Iter����
#include "..\..\..\Array_LinkedList\LinkedList.h"  //LinkedListģ���ࡣ

//////////////////////////////////////////////////////////////////////////////
//	Class:StackAsLinkedList 
//////////////////////////////////////////////////////////////////////////////
class StackAsLinkedList : public Stack
{
    LinkedList<Object*> list;

    class Iter;
public:
    StackAsLinkedList ();
	~StackAsLinkedList ();
	//Added by liuhao for study 2005-11-6.
    void Push (Object&);
    Object& Top () const;
    Object& Pop ();
	virtual void Purge ();
	virtual void Accept (Visitor& visitor) const;
	virtual Iterator& NewIterator() const;

    friend class Iter;
};

class StackAsLinkedList::Iter : public Iterator
{
    StackAsLinkedList const& stack;
    ListElement<Object*> const* position;
public:
    Iter (StackAsLinkedList const&);

    bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();
};
#endif //_STACK_AS_LINKEDLIST_H_