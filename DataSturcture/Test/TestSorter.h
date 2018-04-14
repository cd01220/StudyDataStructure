#ifndef _TEST_SORTER_H_
#define _TEST_SORTER_H_
#include ".\StructAndAlgorithms\Sorter\Sorter.h"
#include ".\StructAndAlgorithms\Sorter\InsertionSorter\StraightInsertionSorter.h"
#include ".\StructAndAlgorithms\Sorter\InsertionSorter\ShellInsertionSorter.h"
#include ".\StructAndAlgorithms\Sorter\InsertionSorter\BinaryInsertionSorter.h"
#include ".\StructAndAlgorithms\Sorter\ExchangeSorter\BubbleSorter.h"
#include ".\StructAndAlgorithms\Sorter\ExchangeSorter\QuickSorter.h"
#include ".\StructAndAlgorithms\Sorter\SelectionSorter\StraightSelectionSorter.h"
#include ".\StructAndAlgorithms\Sorter\SelectionSorter\HeapSorter.h"
#include ".\StructAndAlgorithms\Sorter\MergeSorter\TwoWayMergeSorter.h"
#include ".\StructAndAlgorithms\Sorter\DistributionSorter\BucketSorter.h"
#include ".\StructAndAlgorithms\Sorter\DistributionSorter\RadixSorter.h"

#include ".\StructAndAlgorithms\Sorter\InsertionSorter\BinaryInsertionSorter.h" //希尔排序

#include <time.h>

void testSorter()
{
    //ShellInsertionSorter<unsigned int> sorter;  //希尔插入排序。
    //StraightInsertionSorter<unsigned int> sorter;  //直接插入排序。
    //BinaryInsertionSorter<unsigned int> sorter;    //二分法插入排序。
	//BubbleSorter<unsigned int> sorter; //冒泡排序（交换排序）。
    //MedianOfThreeQuickSorter<unsigned int> sorter; //快速排序（交换排序）。
    //StraightSelectionSorter<unsigned int> sorter;  //直接选择排序。
    //StraightSelectionSorter<unsigned int> sorter;  //堆选择排序。
    //TwoWayMergeSorter<unsigned int> sorter;  //两路规并排序。
    BucketSorter sorter(33333);  //桶排序。
    //RadixSorter sorter;  //基数排序。
	
	//某些算法需要哨兵，所以再对n个元素排序时，需要n+1个存储单元，一般情况
	//下，我们把Array[0]做为哨兵， 相关介绍见书page 138。
	const int iSentinel = 0;//{1,0}

	const unsigned int cuiLength = 30;  //需要排序的元素个数。
    Array<unsigned int> array(cuiLength + iSentinel);
    srand( (unsigned)time( NULL ) );
    for(unsigned int i = 0 + iSentinel; i < cuiLength + iSentinel; ++i)
    {
        array[i] = rand() % 33333;
    }

	bool comma = false;
    unsigned int i;
    for(i = iSentinel; i < cuiLength + iSentinel; ++i)
    {
        if(comma)
            cout << ",";
		else
			cout << "需要排序的数是：";
        cout << array[i];
        comma = true;
    }
	cout << endl;
	
    sorter.Sort(array);

    comma = false;
    for(i = iSentinel; i < cuiLength + iSentinel; ++i)
    {
        if(comma)
            cout << "," << endl;
        cout << array[i];
        comma = true;
    }
}

#endif