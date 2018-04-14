#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <iostream>
using std::ostream;
using std::domain_error;
using std::cout;
using std::endl;
using std::cin;
using std::invalid_argument;
using std::bad_alloc;
using std::out_of_range;
using std::logic_error;
using std::string;

typedef unsigned int HashValue;
//////////////////////////////////////////////////////////////////////////////
//	Class: Object
//////////////////////////////////////////////////////////////////////////////
class Object
{
protected:
    virtual int CompareTo (Object const&) const = 0;
public:
    virtual ~Object ();
    virtual bool IsNull () const;
    virtual int Compare (Object const&) const;
    virtual HashValue Hash () const = 0;
    virtual void Put (ostream&) const = 0;
};

//////////////////////////////////////////////////////////////////////////////
//	Class: NullObject
//////////////////////////////////////////////////////////////////////////////
class NullObject : public Object
{
    static NullObject instance;

    NullObject ();
protected:
    int CompareTo (Object const&) const;
public:
    bool IsNull () const;
    HashValue Hash () const;
    void Put (ostream& s) const;

    static NullObject& Instance ();
};

inline bool operator == (Object const& left, Object const& right)
    { return left.Compare (right) == 0; }

inline bool operator != (Object const& left, Object const& right)
    { return left.Compare (right) != 0; }

inline bool operator <= (Object const& left, Object const& right)
    { return left.Compare (right) <= 0; }

inline bool operator <  (Object const& left, Object const& right)
    { return left.Compare (right) <  0; }

inline bool operator >= (Object const& left, Object const& right)
    { return left.Compare (right) >= 0; }

inline bool operator >  (Object const& left, Object const& right)
    { return left.Compare (right) >  0; }

inline ostream& operator << (ostream& s, Object const& object)
    { object.Put (s); return s; }

//////////////////////////////////////////////////////////////////////////////
//	各种类型的哈希算法。
//////////////////////////////////////////////////////////////////////////////
HashValue Hash(char c);
HashValue Hash(int i);
HashValue Hash(unsigned int i);
HashValue Hash(double d);
HashValue Hash (string const& s);

#endif //_OBJECT_H_