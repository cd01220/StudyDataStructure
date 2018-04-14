
#include ".\BST.h"
//////////////////////////////////////////////////////////////////////////////
//	class AVLTree 接近最优的平衡二叉排序树
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
