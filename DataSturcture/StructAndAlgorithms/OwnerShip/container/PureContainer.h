#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "..\..\Visitor\PureVisitor.h"
#include "..\OwnerShip.h"
#include "..\..\Object\Object.h"

class Iterator;
//////////////////////////////////////////////////////////////////////////////
//Class: HashingVisitor
//����:  ��Ҫ���ڼ���Container�Ĺ�ϣֵ��
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
//����:  ��Ҫ����Container.put()��ȱʡʵ�֡�
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
