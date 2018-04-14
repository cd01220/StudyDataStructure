#include ".\BinaryTree.h"
#include ".\StructAndAlgorithms\OwnerShip\container\Stack\StackAsLinkedList.h"

unsigned int BinaryTree::Degree () const
{
	return 2;
}

Object& BinaryTree::Key () const
{
	return *key;
}

bool BinaryTree::IsLeaf () const
{
	if(IsEmpty())
	{
		return false;
	}
	
	return (left->IsEmpty() && right->IsEmpty());
}

bool BinaryTree::IsEmpty () const
{
	return key == 0;
}

void BinaryTree::AttachKey (Object& object)
{
	if(!IsEmpty())
	{
		throw domain_error("invalid operation");
	}
	
	key = &object;
	left = new BinaryTree ();
	right = new BinaryTree ();
}

Object& BinaryTree::DetachKey ()
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}
	
	if(!IsLeaf())
	{
		throw domain_error("invalid operation");
	}
	
	Object& result = *key;
	key = 0;

	delete left;
	delete right;
	return result;

}

BinaryTree& BinaryTree::Left () const
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

	return *left;
}

BinaryTree& BinaryTree::Right () const
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

	return *right;
}

//modified by liuhao 2005-11-24。
void BinaryTree::AttachLeft (BinaryTree& subtree)
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

    //左子树不为空，引发异常。
	if(!left->IsEmpty())
	{
		throw domain_error("non-empty subtree present");
	}
	delete left;
	left = &subtree;
}

//modified by liuhao 2005-11-24。
void BinaryTree::AttachRight (BinaryTree& subtree)
{
	if(IsEmpty())
	{
		throw domain_error("invalid operation");
	}

	if(!right->IsEmpty())
	{
		throw domain_error("invalid operatrion");
	}

	delete right;
	right = &subtree;
}

BinaryTree& BinaryTree::DetachLeft ()
{
	if (IsEmpty ())
	{
		throw domain_error ("invalid operation");
	}
    BinaryTree& result = *left;
    left = new BinaryTree;
    return result;
}

BinaryTree& BinaryTree::DetachRight ()
{
	if (IsEmpty ())
	{
		throw domain_error ("invalid operation");
	}
    BinaryTree& result = *right;
    right = new BinaryTree;
    return result;
}

BinaryTree& BinaryTree::Subtree (unsigned int i) const
{
	if (i > 1)
	{
		throw domain_error ("parameter error!");
	}
	
	if (IsEmpty ())
	{
		throw domain_error ("invalid operation");
	}

    return (i == 0 ? *left : *right);

}

BinaryTree::BinaryTree () :
    key (0),
    left (0),
    right (0)
{
	;
}

BinaryTree::BinaryTree (Object& _key) :
    key (&_key),
    left (new BinaryTree ()),
    right (new BinaryTree ())
{
	;
}


//说明：如果IsOwner ()返回false， 只说明对key没有所有权， 仍然需要删除子树。
//  相应的， 在AttachKey(), AttachLeft(),AttachRight()操作要求当前树为空，
// DetachKey(), DetachLeft(), DetachRight()返回key， 这样，整个类只有Purge
// 可能删除key。
void BinaryTree::Purge ()
{
    if (!IsEmpty ())
    {
		if (IsOwner ())
			delete key;
		delete left;
		delete right;
		key = 0;
		left = 0;
		right = 0;
    }
}

BinaryTree::~BinaryTree ()
{ Purge (); }

void BinaryTree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (visitor.IsDone ())
		return;
    if (!IsEmpty ())
    {
		visitor.PreVisit (*key);
        left->DepthFirstTraversal (visitor);

		visitor.Visit (*key);

		right->DepthFirstTraversal (visitor);
		visitor.PostVisit (*key);
    }
}

int BinaryTree::CompareTo (Object const& object) const
{
    BinaryTree const& arg = dynamic_cast<BinaryTree const&> (object);
    if (IsEmpty ())
	    return arg.IsEmpty () ? 0 : -1;
    else if (arg.IsEmpty ())
	    return 1;
    else
    {
	    int result = Key ().Compare (arg.Key ());
	    if (result == 0)
	        result = Left ().CompareTo (arg.Left ());
	    if (result == 0)
	        result = Right ().CompareTo (arg.Right ());
	    return result;
    }
}

