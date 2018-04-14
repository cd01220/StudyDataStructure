#ifndef _OWNERSHIP_H_
#define _OWNERSHIP_H_

#include ".\\StructAndAlgorithms\Object\Object.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: Ownership
//////////////////////////////////////////////////////////////////////////////
//修改记录： 因为随书代码导致Container需要多继承，间接导致Tree的子类的 
//SubTree() const的编译问题, 故修改之。 将Ownership 改为Object 的子类。
class Ownership : public Object
{
    bool isOwner;
protected:
    Ownership () ;
    Ownership (Ownership& arg) ;
public:
    void AssertOwnership ();
    void RescindOwnership ();
    bool IsOwner () const;
};

#endif