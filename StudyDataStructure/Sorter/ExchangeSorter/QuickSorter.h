#ifndef _QUICK_SORTER_H_
#define _QUICK_SORTER_H_
#include "../Sorter.h"
#include "../InsertionSorter\StraightInsertionSorter.h"

template <class T>
class QuickSorter : public ExchangeSorter<T>
{
protected:
    static unsigned int const cutOff = 3;  //VC7新特性，在VC6下本语句不能通过编译。

    virtual unsigned int SelectPivot (vector<T>&, unsigned int, unsigned int) = 0;
    void DoSort (vector<T>&, unsigned int, unsigned int);
    void DoSort (vector<T>&);
};

template <class T>
void QuickSorter<T>::DoSort (vector<T>& array, unsigned int left, unsigned int right)
{
    if (right - left + 1 > cutOff)
    {
        unsigned int const p = SelectPivot (array, left, right);
        Swap (array[p], array[right]);
        T& pivot = array[right];
        unsigned int i = left;
        unsigned int j = right - 1U;
        for (;;)
        {
            while (i < j && array[i] < pivot) 
            {
                ++i;
            }
            while (i < j && array[j] > pivot) 
            {
                --j;
            }
            if (i >= j) 
            {
                break;
            }
            Swap (array[i++], array[j--]);
        }
        if (array[i] > pivot)
        {
            //假设array = {6, 10, 33, 32, 8}, 退出for循环后, i = j = 1, 此时需要轴值复位;
            Swap (array[i], pivot);
        }
        if (left < i)
            DoSort (array, left, i - 1U);
        if (right > i)
            DoSort (array, i + 1, right);
    }
}

template <class T>
void QuickSorter<T>::DoSort (vector<T>& array)
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
    unsigned int SelectPivot (vector<T>&, unsigned int, unsigned int);
};

template <class T>
unsigned int MedianOfThreeQuickSorter<T>::SelectPivot (
    vector<T>& vector, unsigned int left, unsigned int right)
{
    unsigned int middle = (left + right) / 2;
    if (vector [left] > vector [middle])
        Swap (left, middle);
    if (vector [left] > vector [right])
        Swap (left, right);
    if (vector [middle] > vector [right])
        Swap (middle, right);
    return middle;
}

#endif

