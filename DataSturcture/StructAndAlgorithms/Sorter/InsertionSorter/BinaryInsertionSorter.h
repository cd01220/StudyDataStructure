#ifndef _BINARY_INSERTION_SORTER_H_
#define _BINARY_INSERTION_SORTER_H_
#include "..\Sorter.h"

template <class T>
class BinaryInsertionSorter : public InsertionSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void BinaryInsertionSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = 1; i < n; ++i)
    {
	T const& tmp = array [i];
	unsigned int left = 0;
	unsigned int right = i;
	while (left < right)
	{
	    unsigned int const middle = (left + right) / 2;
	    if (tmp >= array [middle])
		left = middle + 1;
	    else
		right = middle;
	}
	for (unsigned int j = i; j > left; --j)
	    Swap (array [j - 1U], array [j]);
    }
}
#endif