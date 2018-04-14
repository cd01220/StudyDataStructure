#ifndef _BST_H_
#define _BST_H_

#include ".\BinaryTree.h"
#include ".\SearchTree.h"

//BST: Binary Sort Tree 或 Binary Search Tree
//修改记录：随书代码导制多继承， 致使SearchTree的子类的Subtree()函数只能返回Tree&,
// 故修改之。
class BST : public BinarySearchTree
{
protected:
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void Balance ();
public:
    BST& Left () const;
    BST& Right () const;
    //added by liuhao.
    virtual ~BST() {}

	//added by liuhao 2005-11-25, 随书代码省略了以下几个函数的申明，但是随书代
    //码包含以下函数的定义。
	Object& Find (Object const& object) const;
	Object& FindMin () const;	
    Object& FindMax () const;
	void Insert (Object& object);
    void Withdraw (Object&);
    // added by liuhao.
	bool IsMember (Object const&) const; //BinarySearchTree成员函数。
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //unsigned int Degree () const { return BinaryTree::Degree();}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //bool IsLeaf () const { return BinaryTree::IsLeaf();}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //Object& Key () const {return BinaryTree::Key();}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //void Accept (Visitor& visitor) const{BinaryTree::Accept(visitor);}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //void Purge () {BinaryTree::Purge();}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //Iterator& NewIterator() const {return BinaryTree::NewIterator();}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //int CompareTo(Object const& obj) const{return BinaryTree::CompareTo(obj);}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //bool IsEmpty () const{return BinaryTree::IsEmpty();}
    //added by liuhao 2005-11-25 for 消除C4250警告。
    //void DepthFirstTraversal (PrePostVisitor& visitor) const
    //{
    //    BinaryTree::DepthFirstTraversal(visitor);
    //}
    //added by liuhao 2005-11-25 for 消除C4250警告。 同时，请查看
    //BinaryTree::Subtree()函数的注释，可了解本函数为什么只能定义为
    //返回Tree&, 而不是BST&。
    BST& Subtree (unsigned int i) const;
};

#endif //_BST_H_