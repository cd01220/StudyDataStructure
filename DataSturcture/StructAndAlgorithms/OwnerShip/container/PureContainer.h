#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "..\..\Visitor\PureVisitor.h"
#include "..\OwnerShip.h"
#include "..\..\Object\Object.h"

class Iterator;
//////////////////////////////////////////////////////////////////////////////
//Class: HashingVisitor
//功能:  主要用于计算Container的哈希值。
//////////////////////////////////////////////////////////////////////////////
class HashingVisitor : public Visitor
{
    HashValue value;
public:
    HashingVisitor (HashValue _value) ;
    void Visit (Object& object);
    HashValue Value () const;
};

//////////////////////////////////////////////////////////////////////////////
//Class: PuttingVisitor
//功能:  主要用于Container.put()的缺省实现。
//////////////////////////////////////////////////////////////////////////////
class PuttingVisitor : public Visitor
{
    ostream& stream;
    bool comma;
public:
    PuttingVisitor (ostream& s) : stream (s), comma (false)
	{}
    void Visit (Object& object)
    {
	    if (comma)
            {stream << ", ";}
	    stream << object;
	    comma = true;
    }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: Container
//////////////////////////////////////////////////////////////////////////////
class Container : public Ownership
{
protected:
    unsigned int count;

    Container ();
public:
    virtual unsigned int Count () const;
    virtual bool IsEmpty () const;
    virtual bool IsFull () const;
    virtual HashValue Hash () const;
    virtual void Put (ostream&) const;
    virtual Iterator& NewIterator () const;

    virtual void Purge () = 0;
    virtual void Accept (Visitor&) const = 0;

    //Class Object members.
	int CompareTo (Object const&) const;
};
#endif
