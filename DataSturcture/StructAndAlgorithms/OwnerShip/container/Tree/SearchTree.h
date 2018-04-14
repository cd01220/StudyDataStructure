#ifndef _SEARCHTREE_H_
#define _SEARCHTREE_H_

#include ".\Tree.h"
#include ".\StructAndAlgorithms\OwnerShip\container\SearchableContainer\PureSearchableContainer.h"

//修改记录：随书代码导制多继承， 致使SearchTree的子类的Subtree()函数只能返回Tree&,
// 故修改之。
class SearchTree : public Tree
{
public:
    virtual Object& FindMin () const = 0;
    virtual Object& FindMax () const = 0;
    //原SearchableContainer的成员函数。
    virtual bool IsMember (Object const&) const = 0;
    virtual void Insert (Object&) = 0;
    virtual void Withdraw (Object&) = 0;
    virtual Object& Find (Object const&) const = 0;
	//////////////////////////////////////////////////////////////////////////
	//下面的代码为新添加的代码，目的是为了去掉C4250警告。
	//////////////////////////////////////////////////////////////////////////
	virtual bool IsEmpty() const = 0;
	virtual Iterator& NewIterator() const = 0;
	virtual void Accept (Visitor&) const = 0;
};

#endif //_SEARCHTREE_H_
