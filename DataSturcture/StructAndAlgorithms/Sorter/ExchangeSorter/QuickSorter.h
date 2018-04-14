#ifndef _QUICK_SORTER_H_
#define _QUICK_SORTER_H_
#include "..\Sorter.h"
#include "..\InsertionSorter\StraightInsertionSorter.h"

template <class T>
class QuickSorter : public ExchangeSorter<T>
{

protected:
    static unsigned int const cutOff = 3;  //VC7�����ԣ���VC6�±���䲻��ͨ�����롣

    virtual unsigned int SelectPivot (Array<T>&, unsigned int, unsigned int) = 0;
    void DoSort (Array<T>&, unsigned int, unsigned int);
    void DoSort (Array<T>&);
};

template <class T>
void QuickSorter<T>::DoSort (
    Array<T>& array, unsigned int left, unsigned int right)
{
    if (right - left + 1 > cutOff)
    {
	    unsigned int const p = SelectPivot (array, left, right);
	    Swap (array [p], array [right]);
	    T& pivot = array [right];
	    unsigned int i = left;
	    unsigned int j = right - 1U;
	    for (;;)
	    {
	        while (i < j && array [i] < pivot) 
            {
                ++i;
            }
	        while (i < j && array [j] > pivot) 
            {
                --j;
            }
	        if (i >= j) 
            {
                break;
            }
            Swap (array [i++], array [j--]);
	    }
	    if (array [i] > pivot)
	        Swap (array [i], pivot);
	    if (left < i)
	        DoSort (array, left, i - 1U);
	    if (right > i)
	        DoSort (array, i + 1, right);
    }
}

template <class T>
void QuickSorter<T>::DoSort (Array<T>& array)
{
    DoSort (array, 0, n - 1U);
    StraightInsertionSorter<T> s;
    s.Sort (array);
}
//////////////////////////////////////////////////////////////////////////////
//	Class: MedianOfThreeQuickSorter
//////////////////////////////////////////////////////////////////////////////
template <class T>
class MedianOfThreeQuickSorter : public QuickSorter<T>
{
protected:
    unsigned int SelectPivot (Array<T>&, unsigned int, unsigned int);
};

template <class T>
unsigned int MedianOfThreeQuickSorter<T>::SelectPivot (
    Array<T>& array, unsigned int left, unsigned int right)
{
    unsigned int middle = (left + right) / 2;
    if (array [left] > array [middle])
        Swap (left, middle);
    if (array [left] > array [right])
	    Swap (left, right);
    if (array [middle] > array [right])
	    Swap (middle, right);
    return middle;
}

#endif