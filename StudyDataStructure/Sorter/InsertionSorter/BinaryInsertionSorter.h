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
	//插入排序, 进入for循环之前就已经有一个已经有序的区间, 其唯一元素为array[0].

	for (unsigned int i = 1; i < n; ++i)
	{
		T const& tmp = array [i];
		unsigned int left = 0;
		unsigned int right = i;
		//while 循环中, 每次遍历开始的时候, left为可能插入的最小的下标,  right为最大下标. 
		//也就是说, 排序的范围为 array[left] ~ array[right], 需要排序的区间内的元素个数为 right - left + 1.
		//如果right - left + 1 为偶数(如i=1的时候),  array[middle]为array[left] ~ array[right]的中分线以左的元素.
		//单次遍历结束时, right - left + 1为奇数的情况下, 
		//		如果tmp > array[middle] 剩下范围的元素个数 = 遍历前元素个数 / 2, 
	    //      否则 剩下范围的元素个数 = (遍历前元素个数 + 1) / 2, 
		//***完成整个while循环后, left 就是要array[i]要插入的位置.
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