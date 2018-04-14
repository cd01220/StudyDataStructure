#ifndef _TEST_GENERAL_TREE_H_
#define _TEST_GENERAL_TREE_H_

#include "Tree/GeneralTree.h"
#include "Tree/NaryTree.h"
#include "Tree/BinaryTree.h"
#include "Tree/ExpressionTree.h"
#include "Tree/SearchTree.h"
#include "Tree/BST.h"
#include "Tree/AVLTree.h"

/* 测试深度优先遍历和计算树的高度, 如果要测试其他的遍历算法， 修改Tree::Accept()。 */
void TestGeneralTree()
{
    GeneralTree<int> tree(1);

    tree.AttachSubtree(new GeneralTree<int>(2));
    tree.AttachSubtree(new GeneralTree<int>(3));

    cout << endl;
    cout << tree << endl;
    cout << "Tree's height is:" << tree.Height() << endl;
}

/* 测试深度优先遍历和计算树的高度, 如果要测试其他的遍历算法， 修改Tree::Accept()。 */
void TestNaryTree()
{
	NaryTree<int> tree(3, 1);

	tree.AttachSubtree(0, new NaryTree<int>(3, 12));
	tree.AttachSubtree(1, new NaryTree<int>(3, 13));
	tree.Subtree(0).AttachSubtree(0, new NaryTree<int>(3, 14));
	tree.Subtree(0).AttachSubtree(1, new NaryTree<int>(3, 15));

    cout << endl;
	cout << tree << endl;
	cout << "Tree's height is:" << tree.Height() << endl;
}

void TestBinaryTree()
{
    BinaryTree<int> tree(1);
    tree.AttachLeft(new BinaryTree<int>(2));
    tree.AttachRight(new BinaryTree<int>(3));

    tree.Left().AttachLeft(new BinaryTree<int>(4));
    tree.Left().AttachRight(new BinaryTree<int>(5));

    cout << endl;
    cout << tree << endl;
	cout << "Tree's height is:" << tree.Height() << endl;
}

void TestExpressionTree()
{
    ExpressionTree* tree;
    InfixVisitor visitor;
    char* expression1 = "ab/cd-e*+";

    tree = CreateTreeFromPostExpression(expression1);
    tree->DepthFirstTraversal(visitor);
    cout << endl;
    delete tree;

    char* expression2 = "1+2*3/4";
    tree = CreateTreeFromInExpression(expression2);
    tree->DepthFirstTraversal(visitor);
    cout << endl;
    cout << *tree;
    delete tree;
}

void TestBST()
{
    int array[] = {1,3,5,2,6,7,4,9,10};
    BST<int> tree;

    for (size_t i = 0; i < sizeof(array)/sizeof(int); ++i)
    {
        tree.Insert(array[i]);  
    }

    cout << endl;
    cout << tree << " height is:" << tree.Height() << endl;
}

void TestAVLTree()
{
    int array[] = {1,3,5,2,6,7,4,9,10};
    AVLTree<int> tree;
    for (size_t i = 0; i < sizeof(array)/sizeof(int); ++i)
    {
        tree.Insert(array[i]);  
    }

    cout << endl;
    cout << tree << " height is:" << tree.Height() << endl;
}

#endif