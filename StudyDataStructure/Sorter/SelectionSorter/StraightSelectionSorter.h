#ifndef _STRAIGHT_SELECTION_SORTER_H_
#define _STRAIGHT_SELECTION_SORTER_H_
#include "..\Sorter.h"

template <class T>
class StraightSelectionSorter : public SelectionSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void StraightSelectionSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = n; i > 1; --i)
    {
	    unsigned int max = 0;
	    for (unsigned int j = 1; j < i; ++j)
        {
	        if (array [j] > array [max])
            {
		        max = j;
            }
        }
	    Swap (array [i - 1U], array [max]);
    }
}

#endif