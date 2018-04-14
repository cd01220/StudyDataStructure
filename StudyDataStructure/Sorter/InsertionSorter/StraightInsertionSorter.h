#ifndef _STRAIGHT_INSERTION_SORTER_H_
#define _STRAIGHT_INSERTION_SORTER_H_
#include "../Sorter.h"

template <class T>
class StraightInsertionSorter : public InsertionSorter<T>
{
protected:
    void DoSort (vector<T>&);
};

template <class T>
void StraightInsertionSorter<T>::DoSort (vector<T>& array)
{
	//插入排序, 进入for循环之前就已经有一个已经有序的区间, 其唯一元素为array[0].
	unsigned int i, j;

    for (i = 1; i < n; ++i)
    {
	    for (j = i; j > 0 && array [j - 1U] > array [j]; --j)
		{
	        Swap (array [j], array [j - 1U]);
		}
    }
}
#endif