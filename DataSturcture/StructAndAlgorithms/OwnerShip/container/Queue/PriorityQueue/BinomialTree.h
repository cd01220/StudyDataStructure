#ifndef _BINOMIAL_TREE_H_
#define _BINOMIAL_TREE_H_

#include ".\StructAndAlgorithms\OwnerShip\container\Tree\GeneralTree.h"
class BinomialTree : public GeneralTree
{
    void SwapContents (BinomialTree&);
public:
    BinomialTree (Object&);

    void Add (BinomialTree&);
    BinomialTree& Subtree (unsigned int) const;
};

#endif