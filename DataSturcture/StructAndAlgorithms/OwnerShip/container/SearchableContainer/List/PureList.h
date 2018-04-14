#ifndef _POSITION_H_
#define _POSITION_H_

#include "..\..\..\..\Iterator\Iterator.h" //Position的基类。
#include "..\PureSearchableContainer.h"    //List的基类。
//////////////////////////////////////////////////////////////////////////////
//	Class: Position
//////////////////////////////////////////////////////////////////////////////
class Position : public Iterator
{
};

//////////////////////////////////////////////////////////////////////////////
//	Class: List
//////////////////////////////////////////////////////////////////////////////
class List : public virtual SearchableContainer
{
public:
    virtual Object& operator [] (unsigned int) const = 0;
    virtual Object& operator [] (Position const&) const = 0;
    virtual Position& FindPosition (Object const&) const = 0;
    virtual void Withdraw (Position const&) = 0;
};

#endif