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
    
    //i ����ð�ݽ����������Ԫ�ص�λ��(1 ~ n).  j ����ð�ݿ��ܲ���Ԫ�ؽ�����������±�.
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
    
    //i ����ð�ݽ����������Ԫ�ص��±�(0 ~ n-1).  j ����ð�ݿ��ܲ���Ԫ�ؽ�����������±�.
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
