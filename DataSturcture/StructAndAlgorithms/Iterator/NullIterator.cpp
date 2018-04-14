#include "..\Object\Object.h"
#include "Iterator.h"

NullIterator::NullIterator ()
    {}

void NullIterator::Reset ()
    {}

bool NullIterator::IsDone () const
    { return true; }

Object& NullIterator::operator * () const
    { return NullObject::Instance (); }

void NullIterator::operator ++ ()
    {}