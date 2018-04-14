#ifndef _TEST_PRIORITY_QUEUE_H_
#define _TEST_PRIORITY_QUEUE_H_

#include "PriorityQueue/PriorityQueue.h"
#include "PriorityQueue/BinaryHeap.h"
#include "PriorityQueue/LeftistHeap.h"

void TestBinaryHeap()
{
    int i;
    BinaryHeap<int> heap(32);

    for (i = 0; i < 5; ++i)
    {
        heap.Enqueue(i);
    }
    cout << heap << endl;

    heap.DequeueMin();
    cout << heap;
}

void TestLeftistHeap()
{
    int i;
    LeftistHeap<int> heap;
    for (i = 1; i <= 5; ++i)
    {
        heap.Enqueue(i * 10);
    }

    cout << heap << endl;

}

#endif