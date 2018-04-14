#include ".\NaryTree.h"

//////////////////////////////////////////////////////////////////////////////
//	Class: NaryTree
//////////////////////////////////////////////////////////////////////////////
//�ж�һ���ڵ��Ƿ�ΪҶ�ӽڵ㣬��Ҫ���ڲ��ڵ�Ϊ��׼�����⣬���е��ⲿ�ڵ�Ҳ����
//���ӽڵ㡣
//modified by liuhao 2005-11-22
bool NaryTree::IsLeaf () const
{	
	if(IsEmpty())
    {   
        //���ݶ��壬��������Ҷ�ڵ㡣
		return false;
    }

    //��ǰ�ڵ�������ӽڵ�������ǿ�������ǰ�ڵ�ΪҶ�ӽڵ㡣
	for(unsigned int i = 0; i < degree;i++)
	{
        NaryTree &tree = Subtree(i);
        if(!IsEmpty())
        {
            return false;
        }		
	}
	return true;
}

//modified by liuhao 2005-11-22, �ο�GeneralTree::Purge();
void NaryTree::Purge ()
{
	if(IsEmpty())
	{
		return;
	}

    if(IsOwner())
    {
	    delete key;
        key = 0;
    }

    for(unsigned int i = 0; i < degree; ++i)
	{
		delete subtree[i];
	}		
}

NaryTree::~NaryTree ()
{
	Purge ();
	return;
}

unsigned int NaryTree::Degree () const
{
	return degree;
}

NaryTree::NaryTree (unsigned int _degree) :
    key (0),
    degree (_degree),
    subtree (0)
    {}

NaryTree::NaryTree (unsigned int _degree, Object& _key):
    key (&_key),
    degree (_degree),
    subtree (_degree)
{
    for (unsigned int i = 0; i < degree; ++i)
	subtree [i] = new NaryTree (degree);
}

bool NaryTree::IsEmpty () const
{ 
	return key == 0; 
}

Object& NaryTree::Key () const
{
    if (IsEmpty ())
	    throw domain_error ("invalid operation");
    return *key;
}

void NaryTree::AttachKey (Object& object)
{
    if (!IsEmpty ())
		throw domain_error ("invalid operation");
    key = &object;
    subtree.SetLength (degree);
    for (unsigned int i = 0; i < degree; ++i)
    {
	    subtree [i] = new NaryTree (degree);
    }
}

Object& NaryTree::DetachKey ()
{
    if (!IsLeaf ())
	    throw domain_error ("invalid operation");
    Object& result = *key;
    key = 0;
    for (unsigned int i = 0; i < degree; ++i)
    {
	    delete subtree [i];
    }
    subtree.SetLength (0);
    return result;
}

NaryTree& NaryTree::Subtree (unsigned int i) const
{
    if (IsEmpty ())
		throw domain_error ("invalid operation");
    return *subtree [i];
}

void NaryTree::AttachSubtree (unsigned int i, NaryTree& t)
{
    if (IsEmpty ())
		throw domain_error ("invalid operation");
    if (!subtree [i]->IsEmpty ())
		throw domain_error ("non-empty subtree present");
    delete subtree [i];
    subtree [i] = &t;
}

NaryTree& NaryTree::DetachSubtree (unsigned int i)
{
    if (IsEmpty ())
		{throw domain_error ("invalid operation");}
    NaryTree& result = *subtree [i];
    subtree [i] = new NaryTree (degree);
    return result;
}