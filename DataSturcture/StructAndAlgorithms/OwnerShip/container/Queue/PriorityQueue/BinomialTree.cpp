#include ".\BinomialTree.h"

BinomialTree::BinomialTree (Object& object) :
    GeneralTree(object)
{
}

void BinomialTree::Add (BinomialTree& tree)
{
    if (degree != tree.degree)
	    throw invalid_argument ("incompatible degrees");
    if (*key > *tree.key)
	    SwapContents (tree);
    AttachSubtree (tree);
    
}

BinomialTree& BinomialTree::Subtree (unsigned int i) const
{
    return dynamic_cast<BinomialTree&>(GeneralTree::Subtree (i));
}

void BinomialTree::SwapContents (BinomialTree& tree)
{
    std::swap(key, tree.key);
    std::swap(degree, tree.degree);
    std::swap(list, tree.list);

}