#include "..\..\Iterator\Iterator.h"
#include ".\PureContainer.h"

//////////////////////////////////////////////////////////////////////////////
//Class: HashingVisitor
//功能:  主要用于计算Container的哈希值。
//////////////////////////////////////////////////////////////////////////////

HashingVisitor::HashingVisitor (HashValue _value) : value (_value)
{}

void HashingVisitor::Visit (Object& object)
{ 
    value += object.Hash (); 
}
HashValue HashingVisitor::Value () const
{ 
    return value; 
}

//////////////////////////////////////////////////////////////////////////////
//	Class: Container
//////////////////////////////////////////////////////////////////////////////
Container::Container () :
    count (0)
    {}

unsigned int Container::Count () const
    { return count; }

bool Container::IsEmpty () const
    { return Count () == 0; }

bool Container::IsFull () const
    { return false; }

HashValue Container::Hash () const
{
    HashingVisitor visitor (::Hash (typeid (*this).name ()));
    Accept (visitor);
    return visitor.Value ();
}

Iterator& Container::NewIterator () const
    { return *new NullIterator (); }

int Container::CompareTo (Object const& obj) const
{
    int iRet = 0;
	Container const& arg =	dynamic_cast<Container const&> (obj);
    
    Iterator& itThis = NewIterator();
    Iterator& itArg  = arg.NewIterator();

    while(!itThis.IsDone() && !itArg.IsDone())
    {  
        iRet = (*itThis).Compare (*itArg);
        if(iRet != 0)
            break;

        ++itThis;
        ++itArg;
    }

    if(0 != iRet)
    {
        delete &itThis;
        delete &itArg;
        return iRet;
    }

    if(itThis.IsDone())
    {
        iRet = itArg.IsDone() ? 0 : -1;
    }
    else
    {
        iRet = 1;
    }

    delete &itThis;
    delete &itArg;
	return iRet;
}

void Container::Put (ostream& s) const
{
    PuttingVisitor visitor (s);

    s << typeid (*this).name () << " {";
    Accept (visitor);
    s << "}";
}

