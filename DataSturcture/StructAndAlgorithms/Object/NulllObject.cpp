#include "Object.h" 

//��֤ȫ�ַ�Χ��ֻ��һ��NullObject ��ʵ����
NullObject NullObject::instance;

NullObject::NullObject ()
    {}

bool NullObject::IsNull () const
    { return true; }

int NullObject::CompareTo (Object const&) const
    { return 0; } 

HashValue NullObject::Hash () const
    { return 0; }

void NullObject::Put (ostream& s) const
    { s << "NullObject"; }

NullObject& NullObject::Instance ()
    { return instance; }
