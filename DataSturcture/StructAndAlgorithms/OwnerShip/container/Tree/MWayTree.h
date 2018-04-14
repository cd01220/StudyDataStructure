#ifndef _MWAYTREE_H_
#define _MWAYTREE_H_

#include ".\SearchTree.h"  //class SearchTree����
#include ".\StructAndAlgorithms\Array_LinkedList\Array.h"
class Stack;

class MWayTreeVisitor : public Visitor
{
public:
    virtual void BeginVisit () {}
    virtual void Visit (Object& object) {}
    virtual void EndVisit () {}
};

class MWayTreePutVisitor : public MWayTreeVisitor
{
    ostream& stream;
    bool comma;
public:
    MWayTreePutVisitor (ostream& s) : stream (s), comma (false)
	{}
    virtual void BeginVisit () 
    {
        stream << "{";
        comma = false;
    }
    virtual void Visit (Object& object) 
    {
         if (comma)
            {stream << ", ";}
	    stream << object;
	    comma = true;
    }
    virtual void EndVisit ()
    {
        stream << "}" << endl;
    }
};

///////////////////////////////////////////////////////////////
//class MWayTree
///////////////////////////////////////////////////////////////
class MWayTree : public SearchTree
{
private:	
	//��class Tree�̳����ĺ���������Ϊprivate ��ֹ������
	Object& Key (void) const{return NullObject::Instance ();}

    class Iter;
protected:
    unsigned int const m;
    unsigned int numberOfKeys;
    Array<Object*> key;
	Array<MWayTree*> subtree;

    unsigned int FindIndex (Object const&) const;
public:
	MWayTree (unsigned int degree);
    ~MWayTree ();

    Object& Key (unsigned int) const;
    virtual MWayTree& Subtree (unsigned int i) const;
    // ...
	void DepthFirstTraversal(PrePostVisitor&) const;
	Object& Find (Object const& object) const;
	Object& BinaryFind (Object const& object) const;
	//��M·��������ɾ�������
	void Insert (Object& object);
	virtual Object& FindMin (void) const;
    virtual Object& FindMax (void) const;
	virtual int CompareTo (Object const&) const;
	bool IsEmpty(void) const;
	Iterator& NewIterator(void) const;
	void Purge(void);
	void Accept(Visitor &) const;
	bool IsLeaf(void) const;
	unsigned int Degree(void) const;
	bool IsMember(const Object &) const;
	void Withdraw(Object &);

    //added by liuhao 2005-12-6 for ͨ����ȱ��������ڵ���ʱ�������
    //��ӡ�����Ľṹ��
    virtual void BreadthFirstTraversal (MWayTreeVisitor&) const;
    virtual unsigned int Count () const;
};

class MWayTree::Iter : public Iterator
{
    MWayTree const& tree;
    Stack& stackKeyIndex;
    Stack& stackTree;
    void PutSubtree(MWayTree const&);
public:
    Iter (MWayTree const&);
    ~Iter ();
    void Reset ();
    bool IsDone () const;
    Object& operator * () const;
    void operator ++ ();
};
#endif //_MWAYTREE_H_
