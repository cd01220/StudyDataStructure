#ifndef _BUCKET_SORTER_H_
#define _BUCKET_SORTER_H_
#include "..\Sorter.h"

//说明：BucketSorter并不是一个模板类， 但是其父类为模板类。
class BucketSorter : public DistributionSorter<unsigned int>
{
protected:
    unsigned int const m;
    Array<unsigned int> count;

    void DoSort (Array<unsigned int>&);
public:
    BucketSorter (unsigned int _m) : m (_m), count (_m) {}
};

void BucketSorter::DoSort (Array<unsigned int>& array)
{
    for (unsigned int i = 0; i < m; ++i)
	    count [i] = 0;

    for (unsigned int j = 0; j < n; ++j)
	    ++count [array [j]];

    for (unsigned int i = 0, j = 0; i < m; ++i)
    {
	    for ( ; count [i] > 0; --count [i])
        {    array [j++] = i;}
    }
}

#endif