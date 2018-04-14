#ifndef _SORTER_H_
#define _SORTER_H_

#include ".\StructAndAlgorithms\Array_LinkedList\Array.h"

template <class T>
class Sorter
{
protected:
    unsigned int n;

    static void Swap (T&, T&);
    virtual void DoSort (Array<T>&) = 0;
public:
    void Sort (Array<T>&);
};

template <class T>
void Sorter<T>::Swap (T& x, T& y)
{
    T const tmp = x;
    x = y;
    y = tmp;
}

template <class T>
void Sorter<T>::Sort (Array<T>& array)
{
    n = array.Length ();
    if (n > 0)
    {
	    unsigned int const tmp = array.Base ();
	    array.SetBase (0);
	    DoSort (array);
	    array.SetBase (tmp);
    }
}

//��������
template <class T>
class InsertionSorter : public Sorter<T> {};

//��������
template <class T>
class ExchangeSorter : public Sorter<T> {};

//ѡ������
template <class T>
class SelectionSorter : public Sorter<T> {};

//�鲢����
template <class T>
class MergeSorter : public Sorter<T> {};

//��������
template <class T>
class DistributionSorter : public Sorter<T> {};


#endif