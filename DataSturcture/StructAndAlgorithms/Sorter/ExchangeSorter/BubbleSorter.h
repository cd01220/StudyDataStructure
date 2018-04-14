#ifndef _BUBBLE_SORTER_H_
#define _BUBBLE_SORTER_H_
#include "..\Sorter.h"

template <class T>
class BubbleSorter : public ExchangeSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void BubbleSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = n; i > 1; --i)
    {
	    for (unsigned int j = 0; j < i - 1U; ++j)
        {
	        if (array [j] > array [j + 1])
            {
		        Swap (array [j], array [j + 1]);
            }
        }
    }
}

#endif
