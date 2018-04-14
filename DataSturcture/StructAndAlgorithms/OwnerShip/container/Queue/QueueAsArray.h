#ifndef _QUEUE_AS_ARRAY_H_
#define _QUEUE_AS_ARRAY_H_

#include ".\Queue.h"
#include "..\..\..\Array_LinkedList\Array.h"   //Array模板类
#include "..\..\..\Iterator\Iterator.h"   //Iter的基类。
//////////////////////////////////////////////////////////////////////////////
//	Class: QueueAsArray
//////////////////////////////////////////////////////////////////////////////
class QueueAsArray : public virtual Queue
{
    class Iter;
protected:
    Array<Object*> array;
    unsigned int head;
    unsigned int tail;
public:
    QueueAsArray (unsigned int);
    ~QueueAsArray ();
    // added by liuhao.
    virtual void Accept (Visitor& visitor) const;
	virtual void Purge ();
    virtual Iterator& NewIterator () const;

	Object& Head () const;
	void Enqueue (Object& object);
	Object& Dequeue ();

    friend class Iter;
};

class QueueAsArray::Iter : public Iterator
{
    QueueAsArray const& queue;
    unsigned int position;
public:
    Iter (QueueAsArray const&);
	bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();
};

#endif //_QUEUE_AS_ARRAY_H_