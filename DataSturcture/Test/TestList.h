#ifndef _TEST_LIST_H_
#define _TEST_LIST_H_

//#include "..\StructAndAlgorithms\OwnerShip\container\SearchableContainer\List\PureList.h"
#include "..\StructAndAlgorithms\OwnerShip\container\SearchableContainer\List\OrderedList\OrderedList.h"
//#include "..\StructAndAlgorithms\OwnerShip\container\SearchableContainer\List\SortedList\SortedList.h"

void TestList(void)
{
    ListAsArray list1(10);
    list1.Insert(*new Int(10));
    list1.Insert(*new Int(20));
    cout << list1 << endl;

    ListAsArray list2(10);
    list2.Insert(*new Int(10));
    list2.Insert(*new Int(20));
    list2.Insert(*new Int(30));
    list2.Insert(*new Int(40));

    Position& pos1 = list2.FindPosition(Int(40));
    list2.InsertBefore(pos1, *new Int(50));
    delete &pos1;
    cout << list2 << endl;

    Position& pos2 = dynamic_cast<Position &>(list2.NewIterator());

    while(!pos2.IsDone())
    {
        cout << *pos2 << endl;
        ++pos2;
    }
    delete &pos2;

    if(list1 == list2)
    {
        cout << "list1 == list2" << endl;
    }
    else if(list1 < list2)
    {
        cout << "list1 < list2" << endl;
    }
    else
    {
        cout << "list1 > list2" << endl;
    }

}

//
//void TestSortedListAsArray()
//{
//    SortedListAsArray list1(10);
//    list1.Insert(*new Int(8));
//    list1.Insert(*new Int(4));
//    list1.Insert(*new Int(7));
//    list1.Insert(*new Int(6));
//    cout << list1 << endl;
//
//    SortedListAsArray list2(10);
//    list2.Insert(*new Int(4));
//    list2.Insert(*new Int(6));
//    list2.Insert(*new Int(7));
//    cout << list2 << endl;
//
//    if(list1 == list2)
//    {
//        cout << "list1 == list2" << endl;
//    }
//    else if(list1 < list2)
//    {
//        cout << "list1 < list2" << endl;
//    }
//    else
//    {
//        cout << "list1 > list2" << endl;
//    }
//}


#endif //_TEST_LIST_H_