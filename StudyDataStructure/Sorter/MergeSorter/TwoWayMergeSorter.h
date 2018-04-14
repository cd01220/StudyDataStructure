#ifndef _TWO_WAY_MERGE_SORTER_H_
#define _TWO_WAY_MERGE_SORTER_H_
#include "..\Sorter.h"

template <class T>
class TwoWayMergeSorter : public MergeSorter<T>
{
protected:
    Array<T>* tempArray;

    void Merge (Array<T>&,
	unsigned int, unsigned int, unsigned int);
    void DoSort (Array<T>&, unsigned int, unsigned int);
    void DoSort (Array<T>&);
public:
    TwoWayMergeSorter () : tempArray (0) {}
};

template <class T>
void TwoWayMergeSorter<T>::Merge (Array<T>& array,
    unsigned int left, unsigned int middle, unsigned int right)
{
    unsigned int i = left;
    unsigned int j = left;
    unsigned int k = middle + 1;
    while (j <= middle && k <= right)
    {
	if (array [j] <= array [k])
	    (*tempArray) [i++] = array [j++];
	else
	    (*tempArray) [i++] = array [k++];
    }
    while (j <= middle)
	(*tempArray) [i++] = array [j++];
    while (k <= right)
	(*tempArray) [i++] = array [k++];
    for (i = left; i <= right; ++i)
	array [i] = (*tempArray) [i];
}

template <class T>
void TwoWayMergeSorter<T>::DoSort (Array<T>& array)
{
    tempArray = new Array<T> (n);
    DoSort (array, 0, n - 1U);
    delete tempArray;
    tempArray = 0;
}

//说明：递归式的分治归并算法。
template <class T>
void TwoWayMergeSorter<T>::DoSort (Array<T>& array,
    unsigned int left, unsigned int right)
{
    if (left < right)
    {
	    unsigned int const middle = (left + right) / 2;
	    DoSort (array, left, middle);
	    DoSort (array, middle + 1, right);
	    Merge (array, left, middle, right);
    }
}

#endif