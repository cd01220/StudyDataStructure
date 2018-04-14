//希尔排序。  学习数据结构一书时新加入的排序算法(page 140)。

#ifndef _SHELL_INSERTION_SORTER_H_
#define _SHELL_INSERTION_SORTER_H_
#include "..\Sorter.h"

template <class T>
class ShellInsertionSorter : public InsertionSorter<T>
{
protected:
    void DoSort (Array<T>&);
    void ShellPass(Array<T>&, unsigned int);
	void ShellSort(Array<T>&);
};


template <class T>
void ShellInsertionSorter<T>::ShellPass(Array<T>& array, unsigned int d)
{
	//希尔排序中的一趟排序，d为当前增量。因为当前算法需要array[0]作为哨兵，
	//所以，总共需要排序的元素个数为array.Length () - 1 也就是n-1
    for (int i = d + 1; i <= n - 1; ++i)  //将array[d+1..n]分别插入各组的当前有序区。
    {
        if(array[i] < array[i-d])
        {
            array[0] = array[i];  //array[0]只是暂存单元，不是哨兵!!!

			int j = 0;
            j = i - d;
            do
            {
                array[j+d] = array[j];
                j = j - d;
            }while(j > 0 && array[0] < array[j]);
            array[j+d] = array[0];
        }
    }
}

template <class T>
void ShellInsertionSorter<T>::ShellSort(Array<T>& array)
{
	int iIncreament = 5;
	do{
		iIncreament = iIncreament/3 + 1;
		ShellPass(array, iIncreament);
	}while(iIncreament > 1);

	return;
}

template <class T>
void ShellInsertionSorter<T>::DoSort (Array<T>& array)
{
	ShellSort(array);
}
#endif