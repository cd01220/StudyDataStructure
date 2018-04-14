#ifndef _SORTER_H_
#define _SORTER_H_

template <class T>
class Sorter
{
protected:
	unsigned int n;

	static void Swap (T&, T&);
	virtual void DoSort (vector<T>&) = 0;
public:
	void Sort (vector<T>&);
};

template <class T>
void Sorter<T>::Swap (T& x, T& y)
{
	T const tmp = x;
	x = y;
	y = tmp;
}

template <class T>
void Sorter<T>::Sort (vector<T>& array)
{
	n = array.size();
	if (n > 0)
	{
		DoSort (array);
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