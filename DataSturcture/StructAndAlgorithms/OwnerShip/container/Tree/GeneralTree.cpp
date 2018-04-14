#include ".\GeneralTree.h"

GeneralTree::GeneralTree (Object& _key) :
    key (&_key),
    degree (0),
    list ()
    {}

GeneralTree::~GeneralTree ()
{ Purge (); }

void GeneralTree::Purge ()
{
    ListElement<GeneralTree*> const* ptr;

    if (IsOwner ())
	    delete key;
    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	    delete ptr->Datum ();

    key = 0;
    list.Purge ();
}

//added by liuhao 205-11-19
int GeneralTree::Height () const
{
    //根据定义空树的高度为-1(注：广义树没有空树,因此广义树必须重载本函数。);
    int iMaxSubHeight = 0;
    for (unsigned int i = 0; i < Degree (); ++i)
    {
        iMaxSubHeight = std::max(iMaxSubHeight, Subtree (i).Height() + 1);
    }

    return iMaxSubHeight;
}

unsigned int GeneralTree::Count () const
{
    unsigned int uiRet = 1;
    for (unsigned int i = 0; i < Degree (); ++i)
    {
        uiRet += Subtree (i).Count();
    }

    return uiRet;
}

//added by liuhao 205-11-19, 根据定义，广义树没有空树。
bool GeneralTree::IsEmpty () const
{
    return false;
}

bool GeneralTree::IsLeaf () const
{
    return (degree == 0);
}

unsigned int GeneralTree::Degree () const
{
    return degree;
}

Object& GeneralTree::Key () const
{ return *key; }

GeneralTree& GeneralTree::Subtree (unsigned int i) const
{
    if (i >= degree)
	    throw out_of_range ("invalid subtree index");

    unsigned int j = 0;
    ListElement<GeneralTree*> const* ptr = list.Head ();
    while (j < i && ptr != 0)
    {
	    ++j;
	    ptr = ptr->Next ();
    }
    if (ptr == 0)
	    throw logic_error ("should never happen");
    return *ptr->Datum ();
}

void GeneralTree::AttachSubtree (GeneralTree& t)
{
    list.Append (&t);
    ++degree;
}

GeneralTree& GeneralTree::DetachSubtree (GeneralTree& t)
{
    list.Extract (&t);
    --degree;
    return t;
}
