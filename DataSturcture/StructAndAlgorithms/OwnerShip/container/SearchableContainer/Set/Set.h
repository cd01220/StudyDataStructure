#ifndef _SET_H_
#define _SET_H_

#include ".\StructAndAlgorithms\OwnerShip\container\SearchableContainer\PureSearchableContainer.h"
#include ".\\StructAndAlgorithms\Object\Wrapper\Wrapper.h" //class Wrapper模枝类定义
class Set : public virtual SearchableContainer
{
protected:
    unsigned int universeSize;

public:
    Set (unsigned int n) : universeSize (n) {}

    typedef Wrapper<unsigned int> Element;
};
#endif