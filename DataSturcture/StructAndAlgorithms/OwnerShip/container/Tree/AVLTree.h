
#include ".\BST.h"
//////////////////////////////////////////////////////////////////////////////
//	class AVLTree �ӽ����ŵ�ƽ�����������
//////////////////////////////////////////////////////////////////////////////
class AVLTree : public BST
{
protected:
    int height;

    int BalanceFactor () const;
    void AdjustHeight ();
    void LLRotation ();
    void LRRotation ();
    void RRRotation ();
    void RLRotation ();
    void AttachKey (Object&);
    Object& DetachKey ();
    void Balance ();
public:
    AVLTree ();

    int Height () const;
    AVLTree& Left () const;
    AVLTree& Right () const;
};
