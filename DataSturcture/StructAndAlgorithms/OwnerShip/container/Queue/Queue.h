#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "..\PureContainer.h"  //Containerƒ£∞Â¿‡

//////////////////////////////////////////////////////////////////////////////
//	Class: Queue
//////////////////////////////////////////////////////////////////////////////
class Queue : public virtual Container
{
public:
    virtual Object& Head () const = 0;
    virtual void Enqueue (Object&) = 0;
    virtual Object& Dequeue () = 0;
};

#endif //_QUEUE_H_
