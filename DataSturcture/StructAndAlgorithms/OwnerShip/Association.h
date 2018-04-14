#ifndef _ASSOCIATION_H_
#define _ASSOCIATION_H_

#include "..\Object\Object.h"
#include "Ownership.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: Association
//////////////////////////////////////////////////////////////////////////////
class Association : public Ownership
{
protected:
    Object* key;
    Object* value;

    int CompareTo (Object const&) const;
public:
    Association (Object&);
    Association (Object&, Object&);
    ~Association ();

    Object& Key () const;
    Object& Value () const;

    HashValue Hash () const;
    void Put (ostream&) const;
};

#endif //_ASSOCIATION_H_