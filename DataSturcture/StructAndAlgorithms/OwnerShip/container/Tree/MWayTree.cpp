#include ".\MWayTree.h"
#include "..\Stack\StackAsLinkedList.h"
#include ".\StructAndAlgorithms\OwnerShip\Association.h"
#include ".\StructAndAlgorithms\Object\Wrapper\Wrapper.h"
#include ".\StructAndAlgorithms\OwnerShip\container\Queue\QueueAsLinkedList.h"

MWayTree::~MWayTree ()
{
	Purge();
}

MWayTree& MWayTree::Subtree (unsigned int i) const
{
	return (*subtree[i]);
}

/* 构造函数：初始化m,subtree */
MWayTree::MWayTree(unsigned int degree): m(degree),subtree(degree),key(degree-1,1),numberOfKeys(0)
{
	return ;
}

bool MWayTree::IsMember(const Object &object) const
{
	//modified by liuhao, 2005-11-30.  
	return (&Find(object) == &object);
}

Object& MWayTree::Key(unsigned int i) const
{
    //modified by liuhao, 2005-11-30
    if(i >= 1 && i <= numberOfKeys)
	    return *key[i];

    return NullObject::Instance ();
}

unsigned int MWayTree::Degree(void) const
{
	return m;
}

bool MWayTree::IsLeaf(void) const
{
	if(IsEmpty())
		return false;

	for(unsigned int i = 1; i < m; ++i)
	{
		if(subtree[i]->numberOfKeys != 0)
			return false;
	}
	
	return true;
}

void MWayTree::Accept(Visitor &visitor) const
{
	//modified by liuhao, 2005-11-30
    DepthFirstTraversal (InOrder (visitor)); 
	return ;
}

void MWayTree::Purge(void)
{
    //modified by liuhao, 2005-11-30
    if(numberOfKeys == 0)
        return;

    delete subtree[0];  
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
    {
        cout << *key[i] << endl;
        delete key[i];
        delete subtree[i];
    }
	return ;
}


Iterator& MWayTree::NewIterator(void) const
{
	return *new Iter(*this);
}


bool MWayTree::IsEmpty(void) const
{
	if(numberOfKeys == 0)
		return true;

	return false;
}

//added by liuhao 2005-12-1, 参考了BinaryTree.CompareTo()的实现。
int MWayTree::CompareTo (Object const& object) const
{
	MWayTree const& arg = dynamic_cast<MWayTree const&> (object);
    if (IsEmpty ())
	    return arg.IsEmpty () ? 0 : -1;
    else if (arg.IsEmpty ())
	    return 1;
    else
    {
        unsigned int number = std::min(numberOfKeys, arg.numberOfKeys);
        int result;
        for(unsigned int i = 1; i <= number; ++i)
        {
            result = subtree[i - 1]->CompareTo(*arg.subtree[i - 1]);
            if(0 != result)
            {
                return result;
            }
            
            result = key[i]->Compare (*arg.key[i]);
            if(0 != result)
            {
                return result;
            }

            if(i == number)
            result = subtree[i]->CompareTo(*arg.subtree[i]);
            if(0 != result)
            {
                return result;
            }
        }

        if(numberOfKeys > arg.numberOfKeys)
        {
            result = 1;
        }else if(numberOfKeys > arg.numberOfKeys)
        {
            result = -1;
        }
        else
        {
            result = 0;
        }
	    return result;
    }
}

Object& MWayTree::FindMin() const
{
    if(IsEmpty())
        return NullObject::Instance ();

    if(!subtree[0]->IsEmpty())
        return subtree[0]->FindMin();

	return *key[1];
}

Object& MWayTree::FindMax() const
{
    if(IsEmpty())
        return NullObject::Instance ();

    if(!subtree[numberOfKeys]->IsEmpty())
        return subtree[numberOfKeys]->FindMax();

	return *key[numberOfKeys];
}
 
/*********************************************************
*算法要点： 在遍历T[i-1]之后,遍历T[i]之前，给关键字K[i-1]调用PostVisit(),
*给关键字K[i]调用PostVisit(), 给关键字K[i+1]调用Previsit()。
*********************************************************/
void MWayTree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (!IsEmpty ())
    {
		    for (unsigned int i = 0; i <= numberOfKeys + 1; ++i)
	        {
	            if (i >= 2)
		            visitor.PostVisit (*key [i - 1]);
	            if (i >= 1 && i <= numberOfKeys)
		            visitor.Visit (*key [i]);
	            if (i <= numberOfKeys - 1)
		            visitor.PreVisit (*key [i + 1]);
                if (i <= numberOfKeys)   //随书代码有误， 故修改之。
		            subtree [i]->DepthFirstTraversal (visitor);
	        }
    }
}

Object& MWayTree::Find (Object const& object) const
{
    if (IsEmpty ())
	    return NullObject::Instance ();
    unsigned int i = numberOfKeys;
    while (i > 0)
    {
		int const diff = object.Compare (*key [i]);
		if (diff == 0)
			return *key [i];
		if (diff > 0)
			break;
		--i;
    }
    return subtree [i]->Find (object);
}

unsigned int MWayTree::FindIndex (Object const& object) const
{
    if (IsEmpty ())
		throw domain_error ("invalid operation");
    if (object < *key [1])
		return 0;
    unsigned int left = 1;
    unsigned int right = numberOfKeys;
    while (left < right)
    {
		int const middle = (left + right + 1) / 2;
		if (object >= *key [middle])
			left = middle;
		else
			right = middle - 1U;
    }
    return left;
}

Object& MWayTree::BinaryFind (Object const& object) const
{
    if (IsEmpty ())
		return NullObject::Instance ();
    unsigned int const index = FindIndex (object);
    if (index != 0 && object == *key [index])
		return *key [index];
    else
		return subtree [index]->Find (object);
}

void MWayTree::Insert (Object& object)
{
    if (IsEmpty ())
    {
		subtree [0] = new MWayTree (m);
		key [1] = &object;
		subtree [1] = new MWayTree (m);
		numberOfKeys = 1;
    }
    else
    {
		unsigned int const index = FindIndex (object);
		if (index != 0 && object == *key [index])
			throw invalid_argument ("duplicate key");
		if (numberOfKeys < m - 1U)
		{
			for(unsigned int i = numberOfKeys; i > index; --i)
			{
				key [i + 1] = key [i];
				subtree [i + 1] = subtree [i];
			}
			key [index + 1] = &object;
			subtree [index + 1] = new MWayTree (m);
			++numberOfKeys;
		}
			else
				subtree [index]->Insert (object);
	}
}

void MWayTree::Withdraw (Object& object)
{
    if (IsEmpty ())
	    throw invalid_argument ("object not found");
    unsigned int const index = FindIndex (object);
    if (index != 0 && object == *key [index])
    {
	    if (!subtree [index - 1U]->IsEmpty ())
	    {
	        Object& max = subtree [index - 1U]->FindMax ();
	        key [index] = &max;
	        subtree [index - 1U]->Withdraw (max);
	    }
	    else if (!subtree [index]->IsEmpty ())
	    {
	        Object& min = subtree [index]->FindMin ();
	        key [index] = &min;
	        subtree [index]->Withdraw (min);
	    }
	    else
	    {
	        --numberOfKeys;
	        delete subtree [index];
	        for(unsigned int i = index; i <= numberOfKeys; ++i)
	        {
		        key [i] = key [i + 1];
		        subtree [i] = subtree [i + 1];
	        }
	        if (numberOfKeys == 0)
		        delete subtree [0];
	    }
    }
    else
	    subtree [index]->Withdraw (object);
}

void MWayTree::BreadthFirstTraversal (MWayTreeVisitor& visitor) const
{
    Queue& queue = *new QueueAsLinkedList ();
    queue.RescindOwnership ();

    if (!IsEmpty ())
	    queue.Enqueue (const_cast<MWayTree&> (*this));
    while (!queue.IsEmpty () && !visitor.IsDone ())
    {
		MWayTree const& head =
			dynamic_cast<MWayTree const &> (queue.Dequeue ());

        visitor.BeginVisit();
        for (unsigned int i = 1; i <= head.numberOfKeys; ++i)
        {
            visitor.Visit (head.Key (i));
        }
        visitor.EndVisit();
        unsigned int i;
		for ( i = 0; i <= head.numberOfKeys; ++i)
		{
			MWayTree& child = head.Subtree (i);
			if (!child.IsEmpty ())
            {
			    queue.Enqueue (child);
            }
		}
    }
    delete &queue;
}

unsigned int MWayTree::Count () const
{   
    if(IsEmpty())
        return 0;

    unsigned int uiRet = numberOfKeys;
    for (unsigned int i = 0; i <= numberOfKeys; ++i)
    {
        uiRet += Subtree (i).Count();
    }

    return uiRet;
}
//////////////////////////////////////////////////////////////////////////////
//	Class: MWayTree::Iter
//////////////////////////////////////////////////////////////////////////////
MWayTree::Iter::Iter (MWayTree const& _tree) :
    tree (_tree),
    stackKeyIndex(*new StackAsLinkedList ()),
    stackTree(*new StackAsLinkedList ())
{
    //stackTree没有所有权， 但stackKeyIndex却拥有所有权， 因为stackKeyIndex的内容
    //都是在Iter中new出来的。
    stackTree.RescindOwnership ();
    Reset ();
}

MWayTree::Iter::~Iter ()
{ 
    delete &stackTree;     
    delete &stackKeyIndex; 
}

void MWayTree::Iter::Reset ()
{
    stackTree.Purge ();
    stackKeyIndex.Purge ();
    PutSubtree(tree);
}

bool MWayTree::Iter::IsDone () const
{ 
    return stackTree.IsEmpty (); 
}

Object& MWayTree::Iter::operator * () const
{
    if (!stackTree.IsEmpty ())
    {
		return dynamic_cast<MWayTree&>(stackTree.Top()).Key(dynamic_cast<Int&>(stackKeyIndex.Top()));
    }
    else
		return NullObject::Instance ();
}

void MWayTree::Iter::operator ++ ()
{
    if (stackTree.IsEmpty ())
    {
        return;
    }

    Int &keyIndex = dynamic_cast<Int&>(stackKeyIndex.Top());
    MWayTree &mTree = dynamic_cast<MWayTree&>(stackTree.Top());
    if(keyIndex == static_cast<int>(mTree.numberOfKeys))
    {
        stackTree.Pop();
        stackKeyIndex.Pop();       
        PutSubtree(mTree.Subtree(keyIndex));       

        delete &keyIndex;
    }
    else
    {
        //子树入栈。
        PutSubtree(mTree.Subtree(keyIndex));
        keyIndex = keyIndex + 1;        
    }
}

void MWayTree::Iter::PutSubtree(MWayTree const& _tree)
{    
    if(_tree.IsEmpty())
    {
        return;
    }

    //当前树入栈，keyIndex值为1。
    stackTree.Push(const_cast<MWayTree&>(_tree));
    stackKeyIndex.Push(*new Int(1));    

    //递归的让所有首子树入栈。
    PutSubtree(_tree.Subtree(0));
}

