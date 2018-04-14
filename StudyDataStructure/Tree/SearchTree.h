#ifndef _SEARCHTREE_H_
#define _SEARCHTREE_H_

#include "Tree.h"

template <class T>
class SearchTree : public Tree<T>
{
public:
    virtual T& FindMin () = 0;
    virtual T& FindMax () = 0;
    //ԭSearchableContainer�ĳ�Ա������
    virtual bool IsMember (T&) = 0;
    virtual void Insert (T&) = 0;
    virtual void Withdraw (T&) = 0;
    virtual T& Find (T&) = 0;
	//////////////////////////////////////////////////////////////////////////
	//����Ĵ���Ϊ����ӵĴ��룬Ŀ����Ϊ��ȥ��C4250���档
	//////////////////////////////////////////////////////////////////////////
	virtual bool IsEmpty() = 0;
	virtual void Accept (Visitor&) = 0;
};

#endif //_SEARCHTREE_H_
