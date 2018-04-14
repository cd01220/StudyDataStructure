#ifndef _STRAIGHT_INSERTION_SORTER_H_
#define _STRAIGHT_INSERTION_SORTER_H_

#include "..\Sorter.h"

template <class T>
class StraightInsertionSorter : public InsertionSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void StraightInsertionSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = 1; i < n; ++i)
    {
	    for (unsigned int j = i; j > 0 && array [j - 1U] > array [j]; --j)
	        Swap (array [j], array [j - 1U]);
    }
}
#endif