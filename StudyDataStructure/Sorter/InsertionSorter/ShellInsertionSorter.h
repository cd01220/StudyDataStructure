//ϣ������  ѧϰ���ݽṹһ��ʱ�¼���������㷨(page 140)��

#ifndef _SHELL_INSERTION_SORTER_H_
#define _SHELL_INSERTION_SORTER_H_
#include "../Sorter.h"

template <class T>
class ShellInsertionSorter : public InsertionSorter<T>
{
protected:
	void DoSort (vector<T>&);
	void ShellPass(vector<T>&, unsigned int);
	void ShellSort(vector<T>&);
};


template <class T>
void ShellInsertionSorter<T>::ShellPass(vector<T>& array, unsigned int d)
{
	//ϣ�������е�һ������dΪ��ǰ��������Ϊ��ǰ�㷨��Ҫarray[0]��Ϊ�ڱ���
	//���ԣ��ܹ���Ҫ�����Ԫ�ظ���Ϊarray.Length () - 1 Ҳ����n-1
	for (int i = d + 1; i <= n - 1; ++i)  //��array[d+1..n]�ֱ�������ĵ�ǰ��������
	{
		if(array[i] < array[i-d])
		{
			array[0] = array[i];  //array[0]ֻ���ݴ浥Ԫ�������ڱ�!!!

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
void ShellInsertionSorter<T>::ShellSort(vector<T>& array)
{
	int iIncreament = 5;
	do{
		iIncreament = iIncreament/3 + 1;
		ShellPass(array, iIncreament);
	}while(iIncreament > 1);

	return;
}

template <class T>
void ShellInsertionSorter<T>::DoSort (vector<T>& array)
{
	ShellSort(array);
}
#endif