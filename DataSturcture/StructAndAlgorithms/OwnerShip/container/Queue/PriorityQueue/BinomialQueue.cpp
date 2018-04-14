#include ".\BinomialQueue.h"

BinomialQueue::BinomialQueue ()
{
}

BinomialQueue::~BinomialQueue ()
{
}

void BinomialQueue::AddTree (BinomialTree& tree)
{
    list.Append (&tree);
    count += tree.Count ();
}

void BinomialQueue::RemoveTree (BinomialTree& tree)
{
    list.Extract (&tree);
    count -= tree.Count ();
}

//功能：用于确定队列中哪一棵二项树具有最小根节点。查找过程仅仅是遍历整个链表，
//      找出具有最小关键字的树。
BinomialTree& BinomialQueue::FindMinTree () const
{
    ListElement<BinomialTree*> const* ptr;

    BinomialTree* minTree = 0;
    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
    {
	    BinomialTree* tree = ptr->Datum ();
	    if (minTree == 0 || tree->Key () < minTree->Key ())
	        minTree = tree;
    }
    return *minTree;
}

Object& BinomialQueue::FindMin () const
{
    if (count == 0)
	throw domain_error ("priority queue is empty");
    return FindMinTree ().Key ();
}

void BinomialQueue::Merge (MergeablePriorityQueue& queue)
{
    BinomialQueue& arg = dynamic_cast<BinomialQueue&> (queue);
    LinkedList<BinomialTree*> oldList = list;
    list.Purge ();
    count = 0;
    ListElement<BinomialTree*> const* p = oldList.Head ();
    ListElement<BinomialTree*> const* q = arg.list.Head();
    BinomialTree* carry = 0;
    for (unsigned int i = 0; p || q || carry; ++i)
    {
	    BinomialTree* a = 0;
	    if (p && p->Datum ()->Degree () == i)
	        { a = p->Datum (); p = p->Next (); }
	    BinomialTree* b = 0;
	    if (q && q->Datum ()->Degree () == i)
	        { b = q->Datum (); q = q->Next (); }
	    BinomialTree* sum = Sum (a, b, carry);
	    if (sum)
	        AddTree (*sum);
	    carry = Carry (a, b, carry);
    }
    arg.list.Purge ();
    arg.count = 0;
}

BinomialTree* BinomialQueue::Sum (
    BinomialTree* a, BinomialTree* b, BinomialTree* c)
{
    if (a && !b && !c)
	    return a;
    else if (!a && b && !c)
	    return b;
    else if (!a && !b && c)
	    return c;
    else if (a && b && c)
	    return c;
    else
	    return 0;
}

BinomialTree* BinomialQueue::Carry (
    BinomialTree* a, BinomialTree* b, BinomialTree* c)
{
    if (a && b && !c)
	{ a->Add (*b); return a; }
    else if (a && !b && c)
	{ a->Add (*c); return a; }
    else if (!a && b && c)
	{ b->Add (*c); return b; }
    else if (a && b && c)
	{ a->Add (*b); return a; }
    else
	    return 0;
}

void BinomialQueue::Enqueue (Object& object)
{
    BinomialQueue queue;
    queue.AddTree (*new BinomialTree (object));
    Merge (queue);
}

Object& BinomialQueue::DequeueMin ()
{
    if (count == 0)
	    throw domain_error ("priority queue is empty");

    BinomialTree& minTree = FindMinTree ();
    RemoveTree (minTree);

    BinomialQueue queue;
    while (minTree.Degree () > 0)
    {
	    BinomialTree& child = minTree.Subtree (0);

	    minTree.DetachSubtree (child);
	    queue.AddTree (child);
    }
    Merge (queue);

    Object& result = minTree.Key ();
    minTree.RescindOwnership ();
    delete &minTree;

    return result;
}

void BinomialQueue::Purge ()
{
    if (IsOwner ())
    {
	    ListElement<BinomialTree*> const* ptr;

	    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	        delete ptr->Datum ();
    }
    list.Purge ();
    count = 0;
}

void BinomialQueue::Accept (Visitor& visitor) const
{
    ListElement<BinomialTree*> const* ptr;

    for (ptr = list.Head ();
	    ptr != 0 && !visitor.IsDone (); ptr = ptr->Next ())
    {
	    visitor.Visit (*ptr->Datum ());
    }
}
