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

#include ".\StructAndAlgorithms\Sorter\InsertionSorter\BinaryInsertionSorter.h" //ϣ������

#include <time.h>

void testSorter()
{
    //ShellInsertionSorter<unsigned int> sorter;  //ϣ����������
    //StraightInsertionSorter<unsigned int> sorter;  //ֱ�Ӳ�������
    //BinaryInsertionSorter<unsigned int> sorter;    //���ַ���������
	//BubbleSorter<unsigned int> sorter; //ð�����򣨽������򣩡�
    //MedianOfThreeQuickSorter<unsigned int> sorter; //�������򣨽������򣩡�
    //StraightSelectionSorter<unsigned int> sorter;  //ֱ��ѡ������
    //StraightSelectionSorter<unsigned int> sorter;  //��ѡ������
    //TwoWayMergeSorter<unsigned int> sorter;  //��·�沢����
    BucketSorter sorter(33333);  //Ͱ����
    //RadixSorter sorter;  //��������
	
	//ĳЩ�㷨��Ҫ�ڱ��������ٶ�n��Ԫ������ʱ����Ҫn+1���洢��Ԫ��һ�����
	//�£����ǰ�Array[0]��Ϊ�ڱ��� ��ؽ��ܼ���page 138��
	const int iSentinel = 0;//{1,0}

	const unsigned int cuiLength = 30;  //��Ҫ�����Ԫ�ظ�����
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
			cout << "��Ҫ��������ǣ�";
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