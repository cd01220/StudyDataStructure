#ifndef _BST_H_
#define _BST_H_

#include ".\BinaryTree.h"
#include ".\SearchTree.h"

//BST: Binary Sort Tree �� Binary Search Tree
//�޸ļ�¼��������뵼�ƶ�̳У� ��ʹSearchTree�������Subtree()����ֻ�ܷ���Tree&,
// ���޸�֮��
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

	//added by liuhao 2005-11-25, �������ʡ�������¼������������������������
    //��������º����Ķ��塣
	Object& Find (Object const& object) const;
	Object& FindMin () const;	
    Object& FindMax () const;
	void Insert (Object& object);
    void Withdraw (Object&);
    // added by liuhao.
	bool IsMember (Object const&) const; //BinarySearchTree��Ա������
    //added by liuhao 2005-11-25 for ����C4250���档
    //unsigned int Degree () const { return BinaryTree::Degree();}
    //added by liuhao 2005-11-25 for ����C4250���档
    //bool IsLeaf () const { return BinaryTree::IsLeaf();}
    //added by liuhao 2005-11-25 for ����C4250���档
    //Object& Key () const {return BinaryTree::Key();}
    //added by liuhao 2005-11-25 for ����C4250���档
    //void Accept (Visitor& visitor) const{BinaryTree::Accept(visitor);}
    //added by liuhao 2005-11-25 for ����C4250���档
    //void Purge () {BinaryTree::Purge();}
    //added by liuhao 2005-11-25 for ����C4250���档
    //Iterator& NewIterator() const {return BinaryTree::NewIterator();}
    //added by liuhao 2005-11-25 for ����C4250���档
    //int CompareTo(Object const& obj) const{return BinaryTree::CompareTo(obj);}
    //added by liuhao 2005-11-25 for ����C4250���档
    //bool IsEmpty () const{return BinaryTree::IsEmpty();}
    //added by liuhao 2005-11-25 for ����C4250���档
    //void DepthFirstTraversal (PrePostVisitor& visitor) const
    //{
    //    BinaryTree::DepthFirstTraversal(visitor);
    //}
    //added by liuhao 2005-11-25 for ����C4250���档 ͬʱ����鿴
    //BinaryTree::Subtree()������ע�ͣ����˽Ȿ����Ϊʲôֻ�ܶ���Ϊ
    //����Tree&, ������BST&��
    BST& Subtree (unsigned int i) const;
};

#endif //_BST_H_