#ifndef _OWNERSHIP_H_
#define _OWNERSHIP_H_

#include ".\\StructAndAlgorithms\Object\Object.h"
//////////////////////////////////////////////////////////////////////////////
//	Class: Ownership
//////////////////////////////////////////////////////////////////////////////
//�޸ļ�¼�� ��Ϊ������뵼��Container��Ҫ��̳У���ӵ���Tree������� 
//SubTree() const�ı�������, ���޸�֮�� ��Ownership ��ΪObject �����ࡣ
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