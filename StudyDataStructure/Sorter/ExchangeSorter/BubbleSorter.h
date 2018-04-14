#ifndef _BUBBLE_SORTER_H_
#define _BUBBLE_SORTER_H_
#include "../Sorter.h"

template <class T>
class BubbleSorter : public ExchangeSorter<T>
{
protected:
    void DoSort (vector<T>&);
};

template <class T>
void BubbleSorter<T>::DoSort (vector<T>& array)
{
    #if 0
    
    //i 本次冒泡交换出的最大元素的位置(1 ~ n).  j 本次冒泡可能产生元素交换的区间的下标.
    for (unsigned int i = n; i > 1; --i)
    {
        for (unsigned int j = 0; j < i - 1U; ++j)
        {
            if (array[j] > array[j + 1])
            {
                Swap (array[j], array[j + 1]);
            }
        }
    }

    #else
    
    //i 本次冒泡交换出的最大元素的下标(0 ~ n-1).  j 本次冒泡可能产生元素交换的区间的下标.
    for (unsigned int i = n - 1; i > 0; --i)
    {
        for (unsigned int j = 0; j < i; ++j)
        {
            if (array[j] > array[j + 1])
            {
                Swap (array[j], array[j + 1]);
            }
        }
    }
    
    #endif
}

#endif
