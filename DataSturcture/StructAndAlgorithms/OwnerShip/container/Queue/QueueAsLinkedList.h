#ifndef _QUEUE_AS_LINKEDLIST_H_
#define _QUEUE_AS_LINKEDLIST_H_

#include ".\Queue.h"
#include "..\..\..\Array_LinkedList\LinkedList.h" //LinkedListģ����
#include "..\..\..\Iterator\Iterator.h"   //Iter�Ļ��ࡣ
//////////////////////////////////////////////////////////////////////////////
//	Class: QueueAsLinkedList
//////////////////////////////////////////////////////////////////////////////
class QueueAsLinkedList : public virtual Queue
{
    class Iter;                 //added by liuhao 2005-11-09
protected:
    LinkedList<Object*> list;
public:
    QueueAsLinkedList ();
    ~QueueAsLinkedList ();
	//������麯��, added by liuhao��
    virtual void Accept (Visitor& visitor) const;
	virtual void Purge ();
    virtual Iterator& NewIterator() const;

	Object& Head () const;
	void Enqueue (Object& object);
	Object& Dequeue ();

    friend class Iter;        //added by liuhao 2005-11-09
};

class QueueAsLinkedList::Iter : public Iterator
{
    QueueAsLinkedList const& queue;
    ListElement<Object*> const* position;
public:
    Iter (QueueAsLinkedList const&);

    bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();
};

#endif //_QUEUE_AS_LINKEDLIST_H_