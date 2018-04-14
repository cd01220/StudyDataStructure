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
//  ˵���� ���һ������ľ�������û���ṩ��֮�������κε����������Է���
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
