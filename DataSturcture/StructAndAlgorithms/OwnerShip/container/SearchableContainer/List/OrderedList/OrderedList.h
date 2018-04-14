#ifndef _ORDEREDLIST_H_
#define _ORDEREDLIST_H_

//Array��һ��ģ���࣬����������£� ���ò��ڱ�h�ļ�������������ͷ�ļ�����
//Ϊ����û�취��class Array�ķ���������һ��Array�ࡣ
#include "..\..\..\..\..\Array_LinkedList\Array.h"  
#include "..\PureList.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: OrderedList
//////////////////////////////////////////////////////////////////////////////
class OrderedList : public virtual List
{
public:
    virtual void InsertAfter (Position const&, Object&) = 0;
    virtual void InsertBefore (Position const&, Object&) = 0;
};

//////////////////////////////////////////////////////////////////////////////
//	Class: ListAsArray
//////////////////////////////////////////////////////////////////////////////
class ListAsArray : public virtual OrderedList
{
protected:
    Array<Object*> array;

    class Pos;
public:
    ListAsArray (unsigned int);
    ~ListAsArray ();
    //added by liuhao 2005-11-9
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

	//class OrderedList.
	virtual void InsertAfter (Position const&, Object&);
    virtual void InsertBefore (Position const&, Object&);

	//Container class members.
	virtual void Purge();
	virtual void Accept(Visitor&) const;
	virtual Iterator& NewIterator() const;

    friend class Pos;
};

class ListAsArray::Pos : public Position
{
protected:
    ListAsArray const& list;
    unsigned int offset;
public:
    //added by liuhao.
	Pos(const ListAsArray&, int);
    bool IsDone () const;
	void Reset ();
    Object& operator * () const;
    void operator ++ ();

    friend class ListAsArray;
    friend class SortedListAsArray;
};


#endif
