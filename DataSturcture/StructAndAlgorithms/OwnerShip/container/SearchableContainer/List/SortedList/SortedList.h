#ifndef _SORTEDLIST_H_
#define _SORTEDLIST_H_
/////////////SortedList.h Created by liuhao at 2005-11-10////////////
#include "..\OrderedList\OrderedList.h"

class SortedList : public virtual List
{
};

//class OrderedList : public virtual List
//class ListAsArray : public virtual OrderedList
class SortedListAsArray :
    public virtual SortedList, public virtual ListAsArray
{
private:
    unsigned int FindOffset (Object const&) const;
    //class ListAsArray. ��Ϊ������в�Ӧ����InsertAfter(),InsertBefore()
    //�����ڴ˰�������������private������һ�£���ʾ�Ľ�ֹ�û����á�
    virtual void InsertAfter (Position const&, Object&){}
    virtual void InsertBefore (Position const&, Object&){}
public:
    SortedListAsArray (unsigned int);
    // added by liuhao.
    //class list
    virtual Object& operator [] (unsigned int) const;
    virtual Object& operator [] (Position const&) const;
    virtual Position& FindPosition (Object const&) const;
    virtual void Withdraw (Position const&);
    //class SearchableContainer    
    virtual bool IsMember (Object const&) const;
    virtual void Insert (Object&);
    virtual void Withdraw (Object&);
    virtual Object& Find (Object const&) const;

    //Container class members.
    virtual void Purge();
	virtual void Accept(Visitor& visitor) const;
	virtual Iterator& NewIterator() const;
};

#endif //_SORTEDLIST_H_