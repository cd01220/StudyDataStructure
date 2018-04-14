#ifndef _TESTSTORAGEPOOL_H_
#define _TESTSTORAGEPOOL_H_
#include ".\StructAndAlgorithms\StoragePool\StoragePool.h"

void TestSinglyLinkedPool(void)
{
	SinglyLinkedPool clssA(100);
	int a = sizeof(clssA);
	//void *ptr = clssA.Acquire(50); 
    int * i = new int(12);
}

#endif //#ifndef _TESTSTORAGEPOOL_H_