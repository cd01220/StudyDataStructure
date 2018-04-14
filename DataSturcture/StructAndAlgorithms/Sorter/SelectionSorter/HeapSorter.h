#ifndef _HEAP_SORTER_H_
#define _HEAP_SORTER_H_
#include "..\Sorter.h"

template <class T>
class HeapSorter : public SelectionSorter<T>
{
protected:
    void BuildHeap (Array<T>&);
    void PercolateDown (Array<T>&, unsigned int, unsigned int);
    void DoSort (Array<T>&);
};

//参数：array 数组的引用。length 要考虑的元素个数。i 要渗透的节点的位置。
template <class T>
void HeapSorter<T>::PercolateDown (
    Array<T>& array, unsigned int length, unsigned int i)
{
    while (i <= length / 2)
    {
	    unsigned int child = 2 * i;
	    if (child + 1 <= length
		    && array [child + 1] > array [child])
	        child = child + 1;
	    if (array [i] >= array [child])
	        break;
	    Swap (array [i], array [child]);
	    i = child;
    }
}

template <class T>
void HeapSorter<T>::BuildHeap (Array<T>& array)
{
    for (unsigned int i = n / 2; i > 0; --i)
	    PercolateDown (array, n, i);
}

template <class T>
void HeapSorter<T>::DoSort (Array<T>& array)
{
    array.SetBase (1);
    BuildHeap (array);
    for (unsigned int i = n; i >= 2; --i)
    {
	    Swap (array [i], array [1]);
	    PercolateDown (array, i - 1U, 1);
    }
}

#endif
