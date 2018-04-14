#ifndef _TREE_H_
#define _TREE_H_
#include "../Visitor/PureVisitor.h"


//////////////////////////////////////////////////////////////////////////////
//	Class: PrePostVisitor
//////////////////////////////////////////////////////////////////////////////
template <class T>
class PrePostVisitor : public Visitor<T>
{
public:
    virtual void PreVisit (T&) {}
    virtual void Visit (T&) {}
    virtual void PostVisit (T&) {}
};

//////////////////////////////////////////////////////////////////////////////
//	Class: PreOrder
//////////////////////////////////////////////////////////////////////////////
template <class T>
class PreOrder : public PrePostVisitor<T>
{
    Visitor& visitor;
public:
    PreOrder (Visitor& v) : visitor (v)
    {}
    void PreVisit(T& object)
    { 
        visitor.Visit (object); 
    }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: InOrder
//////////////////////////////////////////////////////////////////////////////
template <class T>
class InOrder : public PrePostVisitor<T>
{
    Visitor& visitor;
public:
    InOrder (Visitor& v) : visitor (v)
    {}
    void Visit(T& object)
    { 
        visitor.Visit (object); 
    }
};

template <class T>
class PostOrder : public PrePostVisitor<T>
{
    Visitor& visitor;
public:
    PostOrder (Visitor& v) : visitor (v)
    {}
    void PostVisit(T& object)
    { 
        visitor.Visit (object); 
    }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: TreePrintVisitor
//////////////////////////////////////////////////////////////////////////////
template <class T>
class TreePrintVisitor : public Visitor<T>
{
private:
    ostream& _os;
    bool comma;

public:
    TreePrintVisitor(ostream& os): _os(os), comma(false)
	{}

    void Visit(T& object)
    {
	    if (comma)
        {
            _os << ", ";
        }
	    _os << object;
	    comma = true;
    }
};

//////////////////////////////////////////////////////////////////////////////
//	Class: Tree
//////////////////////////////////////////////////////////////////////////////
template <class T>
class Tree
{
public:
    virtual T& Key () = 0;
    //随书代码为virtual Tree& Subtree (unsigned int) const = 0; 因为未知原因，
    //原代码不能通过编译， 去掉const 属性后，可编译通过，故修改之。
    virtual Tree& Subtree (unsigned int) = 0;
    virtual bool IsEmpty () = 0;
    virtual bool IsLeaf () = 0;
    virtual unsigned int Degree () = 0;  
    virtual int Height();
    virtual void DepthFirstTraversal (PrePostVisitor<T>&);
    virtual void BreadthFirstTraversal (Visitor<T>&);
    virtual void Accept (Visitor<T>&);
    virtual void Put (ostream&);
};

template <class T>
inline ostream& operator << (ostream& os, Tree<T>& tree)
{ 
    tree.Put(os); 
    return os; 
}

template <class T>
void Tree<T>::DepthFirstTraversal(PrePostVisitor<T>& visitor)
{
    if (visitor.IsDone())
        return;

    if (!IsEmpty())
    {
        visitor.PreVisit(Key());

        //原书代码有误， 故修改之， 并已通过测试。2005-11-19
        if(0 != Degree()) 
        {
            Subtree(0).DepthFirstTraversal (visitor);
        }
        visitor.Visit(Key());
        for (unsigned int i = 1; i < Degree(); ++i)
        {
            Subtree(i).DepthFirstTraversal(visitor);
        }

        visitor.PostVisit(Key());
    }
}

template <class T>
void Tree<T>::BreadthFirstTraversal (Visitor<T>& visitor)
{
    queue<Tree*> queue;

    if (!IsEmpty())
        queue.push(this);

    while (!queue.empty() && !visitor.IsDone())
    {
        Tree* tree = queue.front();
        queue.pop();

        visitor.Visit(tree->Key());
        for (unsigned int i = 0; i < tree->Degree(); ++i)
        {
            Tree& child = tree->Subtree(i);
            if (!child.IsEmpty())
            {
                queue.push(&child);
            }
        }
    }
}

template <class T>
void Tree<T>::Accept(Visitor<T>& visitor)
{
    //DepthFirstTraversal(PreOrder<T>(visitor));   
    //DepthFirstTraversal(InOrder<T>(visitor));         
    //DepthFirstTraversal(PostOrder<T>(visitor)); 
    BreadthFirstTraversal(visitor);
}

template <class T>
int Tree<T>::Height()
{
    //根据定义空树的高度为-1(注：广义树没有空树,因此广义树必须重载本函数。);
    if(IsEmpty())     
        return -1;
    
    int iMaxSubHeight = -1;
    for (unsigned int i = 0; i < Degree (); ++i)
    {
        iMaxSubHeight = max(iMaxSubHeight, Subtree (i).Height());
    }

    return (iMaxSubHeight + 1);
}

template <class T>
void Tree<T>::Put (ostream& os)
{
    TreePrintVisitor<T> visitor(os);

    os << typeid (*this).name() << " {";
    Accept (visitor);
    os << "}";
}

#endif _TREE_H_