#ifndef _SEARCHABLECONTAINER_H_
#define _SEARCHABLECONTAINER_H_

#include "..\PureContainer.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: SearchableContainer
//////////////////////////////////////////////////////////////////////////////
class SearchableContainer : public virtual Container
{
public:
    virtual bool IsMember (Object const&) const = 0;
    virtual void Insert (Object&) = 0;
    virtual void Withdraw (Object&) = 0;
    virtual Object& Find (Object const&) const = 0;
};

#endif //_SEARCHABLECONTAINER_H_