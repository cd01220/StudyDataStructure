#ifndef _SET_AS_ARRAY_H_
#define _SET_AS_ARRAY_H_

#include ".\Set.h"
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h" //class Array 模板类定义
class SetAsArray : public Set
{
    Array<bool> array;
public:
    SetAsArray (unsigned int);
    // ...
    friend SetAsArray operator + (SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator - (SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator * (SetAsArray const&, SetAsArray const&);
    friend bool operator == (SetAsArray const&, SetAsArray const&);
    friend bool operator <= (SetAsArray const&, SetAsArray const&);

    //added by liuhao 2005-12-14
    //class SearchableContainer member function.
    virtual bool IsMember (Object const&) const;
    virtual void Insert (Object&);
    virtual void Withdraw (Object&);
    virtual Object& Find (Object const&) const;
    //class Container member function.
    virtual void Purge ();
    virtual void Accept (Visitor&) const;
};

#endif