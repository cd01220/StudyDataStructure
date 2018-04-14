#include "..\StructAndAlgorithms\OwnerShip\Container\Tree\GeneralTree.h"

void TestGeneralTree()
{
    GeneralTree *tree1 = new GeneralTree(*new Int(20));
    GeneralTree *tree2 = new GeneralTree(*new Int(30));
    GeneralTree *tree3 = new GeneralTree(*new Int(40));
    GeneralTree *tree4 = new GeneralTree(*new Int(50));

    tree1->AttachSubtree(*tree2);
    tree2->AttachSubtree(*tree3);
    tree3->AttachSubtree(*tree4);

    cout << *tree1 << endl;
    cout << tree1->Height() << endl;

    Iterator &iter = tree1->NewIterator();
    while(!iter.IsDone())
    {
        cout << *iter << " ";
        ++iter;
    }

    delete tree1;
}