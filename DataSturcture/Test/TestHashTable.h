#ifndef _TESTHASHTABLE_H_
#define _TESTHASHTABLE_H_

#include "..\StructAndAlgorithms\OwnerShip\Container\SearchableContainer\HashTable\ChainedHashTable.h"
#include "..\StructAndAlgorithms\OwnerShip\Container\SearchableContainer\HashTable\ChainedScatterTable.h"
#include "..\StructAndAlgorithms\OwnerShip\Association.h"

void TestHashTable(void)
{
    ChainedHashTable hashtb1(10);
	hashtb1.Insert(*new Int(1));
	hashtb1.Insert(*new Int(2));
    hashtb1.Insert(*new Int(3));
    hashtb1.Insert(*new Int(4));
    hashtb1.Insert(*new Int(5));    
    cout << hashtb1 << endl;

    ChainedHashTable hashtb2(10);
	//hashtb2.Insert(*new Int(1));
	//hashtb2.Insert(*new Int(2));
 //   hashtb2.Insert(*new Int(3));
 //   hashtb2.Insert(*new Int(4));
 //   hashtb2.Insert(*new Int(6));
    cout << hashtb2 << endl;

    Iterator& iter1 = hashtb1.NewIterator();
    while(!iter1.IsDone())
    {
        cout << *iter1 << ",";
        ++iter1;
    }
    delete &iter1;
    cout << endl;

    Iterator& iter2 = hashtb2.NewIterator();
    while(!iter2.IsDone())
    {
        cout << *iter2 << ",";
        ++iter2;
    }
    delete &iter2;
    cout << endl;

    if(hashtb1 == hashtb2)
    {
        cout << "hashtb1 == hashtb2" << endl;
    }
    else if(hashtb1 < hashtb2)
    {
        cout << "hashtb1 < hashtb2" << endl;
    }
    else
    {
        cout << "hashtb1 > hashtb2" << endl;
    }
}

void TestHashTable1(void)
{
	ChainedHashTable hashtb(10);

    hashtb.Insert(*new Association(*new Int(5), *new String("this")));
    hashtb.Insert(*new Association(*new Int(14), *new String("that")));
    hashtb.Insert(*new Association(*new Int(27), *new String("are")));
    hashtb.Insert(*new Association(*new Int(26), *new String("liuhao")));

	cout << hashtb << endl;
}

void TestHashTable2(void)
{
	ChainedScatterTable hashtb1(100);

    Int *int1 = new Int(26);
    Int *int2 = new Int(56);
    Int *int3 = new Int(57);

    hashtb1.Insert(*new Int(5));
    hashtb1.Insert(*new Int(14));
    hashtb1.Insert(*new Int(27));
    hashtb1.Insert(*int1);
    hashtb1.Insert(*int2);
    hashtb1.Insert(*int3);
    hashtb1.Insert(*new Int(58));
    hashtb1.Insert(*new Int(59));

    //hashtb1.Withdraw(*int1);
    //hashtb1.Withdraw(*int2);
    //hashtb1.Withdraw(*int3);
	cout << hashtb1 << endl;

    ChainedScatterTable hashtb2(10);
    hashtb2.Insert(*new Int(15));
    hashtb2.Insert(*new Int(14));
    hashtb2.Insert(*new Int(27));
    hashtb2.Insert(*new Int(26));
	cout << hashtb2 << endl;

    if(hashtb1 == hashtb2)
    {
        cout << "hashtb1 == hashtb2" << endl;
    }
    else if(hashtb1 < hashtb2)
    {
        cout << "hashtb1 < hashtb2" << endl;
    }
    else
    {
        cout << "hashtb1 > hashtb2" << endl;
    }
}
#endif //_TESTHASHTABLE_H_