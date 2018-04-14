#ifndef _STACK_H_
#define _STACK_H_

#include "..\PureContainer.h"   //class Container »ùÀà¡£

//////////////////////////////////////////////////////////////////////////////
//	Class: Stack
//////////////////////////////////////////////////////////////////////////////
class Stack : public virtual Container
{
public:
    virtual Object& Top () const = 0;
    virtual void Push (Object&) = 0;
    virtual Object& Pop () = 0;
};

#endif //_STACK_H_