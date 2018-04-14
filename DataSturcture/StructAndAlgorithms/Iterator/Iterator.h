#ifndef _ITERATOR_H_
#define _ITERATOR_H_
#include "..\Object\Object.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: Iterator  
//////////////////////////////////////////////////////////////////////////////
class Iterator
{
public:	
	virtual ~Iterator ()  {}
    virtual void Reset () = 0;
    virtual bool IsDone () const = 0;
    virtual Object& operator * () const = 0;
    virtual void operator ++ () = 0;
};

//////////////////////////////////////////////////////////////////////////////
//	Class: NullIterator  
//  说明： 如果一个特殊的具体容器没有提供与之关联的任何迭代器，可以返回
//    NullIterator.
//////////////////////////////////////////////////////////////////////////////
class NullIterator : public Iterator
{
public:
    NullIterator ();
    void Reset ();
    bool IsDone () const;
    Object& operator * () const;
    void operator ++ ();
};

#endif //_ITERATOR_H_
