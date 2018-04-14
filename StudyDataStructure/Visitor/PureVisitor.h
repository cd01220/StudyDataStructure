#ifndef _PUREVISITOR_H_
#define _PUREVISITOR_H_

//////////////////////////////////////////////////////////////////////////////
//	Class: Visitor
//////////////////////////////////////////////////////////////////////////////
template <class T>
class Visitor
{
public:
    virtual void Visit (T&) = 0;
    virtual bool IsDone () const
	{ 
        return false; 
    }
};

#endif //_PUREVISITOR_H_