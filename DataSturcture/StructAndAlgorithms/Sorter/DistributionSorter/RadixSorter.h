#ifndef _RADIX_SORTER_H_
#define _RADIX_SORTER_H_
#include "..\Sorter.h"

class RadixSorter : public DistributionSorter<unsigned int>
{
protected:
    static unsigned int const r;
    static unsigned int const R;
    static unsigned int const p;

    Array<unsigned int> count;

    void DoSort (Array<unsigned int>&);
public:
    RadixSorter () : count (R) {}
};

unsigned int const RadixSorter::r = 8;
unsigned int const RadixSorter::R = 1 << r;
unsigned int const RadixSorter::p = (sizeof(unsigned int) * 8 + r - 1U) / r;

void RadixSorter::DoSort (Array<unsigned int>& array)
{
    Array<unsigned int> tempArray (n);
    for (unsigned int i = 0; i < p; ++i)
    {
	for (unsigned int j = 0; j < R; ++j)
	    count [j] = 0;
	for (unsigned int k = 0; k < n; ++k)
	{
	    ++count [(array [k] >> (r * i)) & (R - 1U)];
	    tempArray [k] = array [k];
	}
	unsigned int pos = 0;
	for (unsigned int j = 0; j < R; ++j)
	{
	    unsigned int const tmp = count [j];
	    count [j] = pos;
	    pos += tmp;
	}
	for (unsigned int k = 0; k < n; ++k)
	{
	    unsigned int j =
		(tempArray [k] >> (r * i)) & (R - 1U);
	    array [count [j]++] = tempArray [k];
	}
    }
}
#endif