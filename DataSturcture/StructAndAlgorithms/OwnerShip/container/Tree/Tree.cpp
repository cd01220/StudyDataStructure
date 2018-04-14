#include ".\Tree.h"
#include "..\Stack\StackAsLinkedList.h"
#include "..\Queue\QueueAsLinkedList.h"

using std::max;

void Tree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (visitor.IsDone ())
		return;
    if (!IsEmpty ())
    {
		visitor.PreVisit (Key ());

        //原书代码有误， 故修改之， 并已通过测试。2005-11-19
        if(0 != Degree ()) 
        {
            Subtree (0).DepthFirstTraversal (visitor);
        }
        visitor.Visit(Key ());
		for (unsigned int i = 1; i < Degree (); ++i)
		{
			Subtree (i).DepthFirstTraversal (visitor);
		}
        
		visitor.PostVisit (Key ());
    }
}

void Tree::BreadthFirstTraversal (Visitor& visitor) const
{
    Queue& queue = *new QueueAsLinkedList ();
    queue.RescindOwnership ();

    if (!IsEmpty ())
	    queue.Enqueue (const_cast<Tree&> (*this));
    while (!queue.IsEmpty () && !visitor.IsDone ())
    {
		Tree const& head =
			dynamic_cast<Tree const &> (queue.Dequeue ());

		visitor.Visit (head.Key ());
		for (unsigned int i = 0; i < head.Degree (); ++i)
		{
			Tree& child = head.Subtree (i);
			if (!child.IsEmpty ())
            {
			    queue.Enqueue (child);
            }
		}
    }
    delete &queue;
}



void Tree::Accept (Visitor& visitor) const
{
	DepthFirstTraversal (InOrder (visitor));         
}

int Tree::Height () const
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

unsigned int Tree::Count () const
{   
    if(IsEmpty())
        return 0;

    unsigned int uiRet = 1;
    for (unsigned int i = 0; i < Degree (); ++i)
    {
        uiRet += Subtree (i).Count();
    }

    return uiRet;
}

Iterator& Tree::NewIterator() const
{
	return *new Iter(*this);
}


//////////////////////////////////////////////////////////////////////////////
//	Class: Tree::Iter
//////////////////////////////////////////////////////////////////////////////
Tree::Iter::Iter (Tree const& _tree) :
    tree (_tree),
    stack (*new StackAsLinkedList ())
{
    stack.RescindOwnership ();
    Reset ();
}

Tree::Iter::~Iter ()
    { delete &stack; }

void Tree::Iter::Reset ()
{
    stack.Purge ();
    if (!tree.IsEmpty ())
		stack.Push (const_cast<Tree&> (tree));
}

bool Tree::Iter::IsDone () const
    { return stack.IsEmpty (); }

Object& Tree::Iter::operator * () const
{
    if (!stack.IsEmpty ())
    {
		Tree const& top =
			dynamic_cast<Tree const&> (stack.Top ());
		return top.Key ();
    }
    else
		return NullObject::Instance ();
}

void Tree::Iter::operator ++ ()
{
    if (!stack.IsEmpty ())
    {
		Tree const& top =
			dynamic_cast<Tree const&> (stack.Pop ());

		for (int i = top.Degree () - 1; i >= 0; --i)
		{
			Tree& subtree = top.Subtree (i);
			if (!subtree.IsEmpty ())
				stack.Push (subtree);
		}
    }
}