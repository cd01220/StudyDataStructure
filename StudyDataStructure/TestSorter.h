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
    //ShellInsertionSorter<unsigned int> sorter;  //ϣ����������
    //StraightInsertionSorter<unsigned int> sorter;  //ֱ�Ӳ�������
    //BinaryInsertionSorter<unsigned int> sorter;    //���ַ���������
	//BubbleSorter<unsigned int> sorter; //ð�����򣨽������򣩡�
    MedianOfThreeQuickSorter<unsigned int> sorter; //�������򣨽������򣩡�
    //StraightSelectionSorter<unsigned int> sorter;  //ֱ��ѡ������
    //StraightSelectionSorter<unsigned int> sorter;  //��ѡ������
    //TwoWayMergeSorter<unsigned int> sorter;  //��·�沢����
    //BucketSorter sorter(33333);  //Ͱ����
    //RadixSorter sorter;  //��������
	
	//ĳЩ�㷨��Ҫ�ڱ��������ڶ�n��Ԫ������ʱ����Ҫn+1���洢��Ԫ��һ�����
	//�£����ǰ�Array[0]��Ϊ�ڱ��� ��ؽ��ܼ���page 138��
	const int sentinel = 0;//{1,0}

	const unsigned int elementsNumber = 5;  //��Ҫ�����Ԫ�ظ�����
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
			cout << "��Ҫ���������: ";
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
			cout << "������      : ";
        cout << array[i];
        comma = true;
    }
}

#endif