#ifndef _TESTTREE_H_
#define _TESTTREE_H_

#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\Tree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\NaryTree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\BinaryTree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\SearchTree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\MWayTree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\BTree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\ExpressionTree.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\BST.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\AVLTree.h"

/* 测试深度优先遍历和计算树的高度。 */
void TestNaryTree()
{
	NaryTree& NaTr1 = *new NaryTree(3, *new Int(11));

	NaTr1.AttachSubtree(0, *new NaryTree(3, *new Int(12)));
	NaTr1.AttachSubtree(1, *new NaryTree(3, *new Int(13)));
	NaTr1.Subtree(0).AttachSubtree(0, *new NaryTree(3, *new Int(14)));
	NaTr1.Subtree(0).AttachSubtree(1, *new NaryTree(3, *new Int(15)));

	cout << NaTr1 << endl;

	cout << "Tree's height is:" << NaTr1.Height() << endl;

    delete &NaTr1;
}

void TestBST()
{
    AVLTree tree;
    tree.Insert(*new Int(1));  
    tree.Insert(*new Int(3));  
    tree.Insert(*new Int(5));
    tree.Insert(*new Int(2));
    tree.Insert(*new Int(6));
    tree.Insert(*new Int(7));
    tree.Insert(*new Int(4));

    Iterator& iter = tree.NewIterator();
    while(!iter.IsDone())
    {
        cout << *iter << "  ";
        ++iter;
    }

    cout << tree << " height is:" << tree.Height() << endl;   
}

void TestMWayTree()
{
    MWayTree tree1(4);     
    tree1.Insert(*new Int(6));     
    tree1.Insert(*new Int(9));     
    tree1.Insert(*new Int(10));       
    tree1.Insert(*new Int(1));
    cout << tree1 << endl;

    tree1.Withdraw(Int(1));
}

void TestBTree()
{
    BTree tree1(4);
    tree1.Insert(*new Int(6));
    tree1.Insert(*new Int(9));
    tree1.Insert(*new Int(10));
    tree1.Insert(*new Int(21));
    tree1.Insert(*new Int(26));
    tree1.Insert(*new Int(29));
    tree1.Insert(*new Int(210));
    tree1.Insert(*new Int(31));
    tree1.Insert(*new Int(36));
    tree1.Insert(*new Int(39));
    tree1.Insert(*new Int(310));

    //tree1.Withdraw(Int(6));
    tree1.Withdraw(Int(9));
    tree1.Withdraw(Int(10));
    tree1.Withdraw(Int(21));
    tree1.Withdraw(Int(26));
    //tree1.Withdraw(Int(29));
    //tree1.Withdraw(Int(210));
    //tree1.Withdraw(Int(31));
    //tree1.Withdraw(Int(36));
    //tree1.Withdraw(Int(39));
    //tree1.Withdraw(Int(310));
    cout << tree1 << endl << "Count() is: " << tree1.Count() << endl;

    MWayTreePutVisitor visitor(cout);
    tree1.BreadthFirstTraversal(visitor);

}

#endif //_TESTTREE_H_