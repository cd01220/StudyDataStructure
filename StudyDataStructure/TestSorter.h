#ifndef _TEST_SORTER_H_
#define _TEST_SORTER_H_
#include <time.h>

#include "Sorter\Sorter.h"
#include "Sorter\InsertionSorter\StraightInsertionSorter.h"
#include "Sorter\InsertionSorter\ShellInsertionSorter.h"
#include "Sorter\InsertionSorter\BinaryInsertionSorter.h"
#include ".\Sorter\ExchangeSorter\BubbleSorter.h"
#include ".\Sorter\ExchangeSorter\QuickSorter.h"
//#include ".\Sorter\SelectionSorter\StraightSelectionSorter.h"
//#include ".\Sorter\SelectionSorter\HeapSorter.h"
//#include ".\Sorter\MergeSorter\TwoWayMergeSorter.h"
//#include ".\Sorter\DistributionSorter\BucketSorter.h"
//#include ".\Sorter\DistributionSorter\RadixSorter.h"

void TestSorter()
{
    //ShellInsertionSorter<unsigned int> sorter;  //希尔插入排序。
    //StraightInsertionSorter<unsigned int> sorter;  //直接插入排序。
    //BinaryInsertionSorter<unsigned int> sorter;    //二分法插入排序。
	//BubbleSorter<unsigned int> sorter; //冒泡排序（交换排序）。
    MedianOfThreeQuickSorter<unsigned int> sorter; //快速排序（交换排序）。
    //StraightSelectionSorter<unsigned int> sorter;  //直接选择排序。
    //StraightSelectionSorter<unsigned int> sorter;  //堆选择排序。
    //TwoWayMergeSorter<unsigned int> sorter;  //两路规并排序。
    //BucketSorter sorter(33333);  //桶排序。
    //RadixSorter sorter;  //基数排序。
	
	//某些算法需要哨兵，所以在对n个元素排序时，需要n+1个存储单元，一般情况
	//下，我们把Array[0]做为哨兵， 相关介绍见书page 138。
	const int sentinel = 0;//{1,0}

	const unsigned int elementsNumber = 5;  //需要排序的元素个数。
    vector<unsigned int> array(elementsNumber + sentinel);
    srand( (unsigned)time( NULL ) );
	unsigned int i;
    for(i = 0 + sentinel; i < elementsNumber + sentinel; ++i)
    {
        array[i] = rand() % 33;
    }

	bool comma = false;
    for(i = sentinel; i < elementsNumber + sentinel; ++i)
    {
        if(comma)
            cout << ",";
		else
			cout << "需要排序的数是: ";
        cout << array[i];
        comma = true;
    }
	cout << endl;
	
    sorter.Sort(array);

    comma = false;
    for(i = sentinel; i < elementsNumber + sentinel; ++i)
    {
        if(comma)
            cout << ",";
		else
			cout << "排序结果      : ";
        cout << array[i];
        comma = true;
    }
}

#endif