#ifndef _SEARCHTREE_H_
#define _SEARCHTREE_H_

#include ".\Tree.h"
#include ".\StructAndAlgorithms\OwnerShip\container\SearchableContainer\PureSearchableContainer.h"

//�޸ļ�¼��������뵼�ƶ�̳У� ��ʹSearchTree�������Subtree()����ֻ�ܷ���Tree&,
// ���޸�֮��
class SearchTree : public Tree
{
public:
    virtual Object& FindMin () const = 0;
    virtual Object& FindMax () const = 0;
    //ԭSearchableContainer�ĳ�Ա������
    virtual bool IsMember (Object const&) const = 0;
    virtual void Insert (Object&) = 0;
    virtual void Withdraw (Object&) = 0;
    virtual Object& Find (Object const&) const = 0;
	//////////////////////////////////////////////////////////////////////////
	//����Ĵ���Ϊ����ӵĴ��룬Ŀ����Ϊ��ȥ��C4250���档
	//////////////////////////////////////////////////////////////////////////
	virtual bool IsEmpty() const = 0;
	virtual Iterator& NewIterator() const = 0;
	virtual void Accept (Visitor&) const = 0;
};

#endif //_SEARCHTREE_H_
