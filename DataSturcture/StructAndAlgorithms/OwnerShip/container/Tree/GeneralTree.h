#ifndef _GENERALTREE_H_
#define _GENERALTREE_H_

#include ".\Tree.h"
#include ".\StructAndAlgorithms\Array_LinkedList\LinkedList.h" //LinkedListƒ£∞Â¿‡
//////////////////////////////////////////////////////////////////////////////
//	Class: GeneralTree
//////////////////////////////////////////////////////////////////////////////
class GeneralTree : public Tree
{
protected:
    Object* key;
    unsigned int degree;
    LinkedList<GeneralTree*> list;
public:
    GeneralTree (Object&);
    ~GeneralTree ();

    //Tree class members.
    Object& Key () const;
    GeneralTree& Subtree (unsigned int) const;
    bool IsEmpty () const;
    bool IsLeaf () const;
    unsigned int Degree () const;
    int Height () const;

    virtual  void AttachSubtree (GeneralTree&);
    virtual GeneralTree& DetachSubtree (GeneralTree&);
    // added by liuhao 2005-11-19
    //Container class members.
	void Purge();
    virtual unsigned int Count () const;
};


#endif  //_GENERALTREE_H_