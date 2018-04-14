#ifndef _TREE_H_
#define _TREE_H_

#include "..\PureContainer.h"
#include "..\..\..\Iterator\Iterator.h"   //Iter的基类。
class Stack;

//////////////////////////////////////////////////////////////////////////////
//	Class: PrePostVisitor
//////////////////////////////////////////////////////////////////////////////
class PrePostVisitor : public Visitor
{
public:
    virtual void PreVisit (Object&) {}
    virtual void Visit (Object&) {}
    virtual void PostVisit (Object&) {}
};

//////////////////////////////////////////////////////////////////////////////
//	Class: PreOrder
//////////////////////////////////////////////////////////////////////////////
class PreOrder : public PrePostVisitor
{
    Visitor& visitor;
public:
    PreOrder (Visitor& v) : visitor (v)
	{}
    void PreVisit (Object& object)
	{ visitor.Visit (object); }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: InOrder
//////////////////////////////////////////////////////////////////////////////
class InOrder : public PrePostVisitor
{
    Visitor& visitor;
public:
    InOrder (Visitor& v) : visitor (v)
	{}
    void Visit (Object& object)
	{ visitor.Visit (object); }
};

class PostOrder : public PrePostVisitor
{
    Visitor& visitor;
public:
    PostOrder (Visitor& v) : visitor (v)
	{}
    void PostVisit (Object& object)
	{ visitor.Visit (object); }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: Tree
//////////////////////////////////////////////////////////////////////////////
class Tree : public virtual Container
{
    class Iter;
public:
    virtual Object& Key () const = 0;
    //随书代码为virtual Tree& Subtree (unsigned int) const = 0; 因为未知原因，
    //原代码不能通过编译， 去掉const 属性后，可编译通过，故修改之。
    virtual Tree& Subtree (unsigned int) const = 0;
    virtual bool IsEmpty () const = 0;
    virtual bool IsLeaf () const = 0;
    virtual unsigned int Degree () const = 0;  
    virtual int Height () const;
    virtual void DepthFirstTraversal (PrePostVisitor&) const;
    virtual void BreadthFirstTraversal (Visitor&) const;
    virtual void Accept (Visitor&) const;
	virtual Iterator& NewIterator() const;
    
    //added by liuhao 2005-12-10;
    virtual unsigned int Count () const;

};

//////////////////////////////////////////////////////////////////////////////
//	Class: Tree::Iter
//////////////////////////////////////////////////////////////////////////////
class Tree::Iter : public Iterator
{
    Tree const& tree;
    Stack& stack;
public:
    Iter (Tree const&);
    ~Iter ();
    void Reset ();
    bool IsDone () const;
    Object& operator * () const;
    void operator ++ ();
};

#endif _TREE_H_