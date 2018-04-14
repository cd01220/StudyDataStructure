#ifndef _BINARY_INSERTION_SORTER_H_
#define _BINARY_INSERTION_SORTER_H_
#include "../Sorter.h"

template <class T>
class BinaryInsertionSorter : public InsertionSorter<T>
{
protected:
	void DoSort (vector<T>&);
};

template <class T>
void BinaryInsertionSorter<T>::DoSort (vector<T>& array)
{
	//��������, ����forѭ��֮ǰ���Ѿ���һ���Ѿ����������, ��ΨһԪ��Ϊarray[0].

	for (unsigned int i = 1; i < n; ++i)
	{
		T const& tmp = array [i];
		unsigned int left = 0;
		unsigned int right = i;
		//while ѭ����, ÿ�α�����ʼ��ʱ��, leftΪ���ܲ������С���±�,  rightΪ����±�. 
		//Ҳ����˵, ����ķ�ΧΪ array[left] ~ array[right], ��Ҫ����������ڵ�Ԫ�ظ���Ϊ right - left + 1.
		//���right - left + 1 Ϊż��(��i=1��ʱ��),  array[middle]Ϊarray[left] ~ array[right]���з��������Ԫ��.
		//���α�������ʱ, right - left + 1Ϊ�����������, 
		//		���tmp > array[middle] ʣ�·�Χ��Ԫ�ظ��� = ����ǰԪ�ظ��� / 2, 
	    //      ���� ʣ�·�Χ��Ԫ�ظ��� = (����ǰԪ�ظ��� + 1) / 2, 
		//***�������whileѭ����, left ����Ҫarray[i]Ҫ�����λ��.
		while (left < right)
		{
			unsigned int const middle = (left + right) / 2;
			if (tmp >= array[middle])
				left = middle + 1;
			else
				right = middle;
		}
		for (unsigned int j = i; j > left; --j)
			Swap (array[j], array[j - 1U]);
	}
}
#endif