#ifndef _TESTQUEUE_H_
#define _TESTQUEUE_H_

#include "..\StructAndAlgorithms\OwnerShip\container\Queue\QueueAsLinkedList.h"
#include "..\StructAndAlgorithms\OwnerShip\container\Queue\PriorityQueue\BinaryHeap.h"
#include "..\StructAndAlgorithms\OwnerShip\container\Queue\PriorityQueue\LeftistHeap.h"
#include "..\StructAndAlgorithms\OwnerShip\container\Queue\PriorityQueue\BinomialQueue.h"
#include "..\StructAndAlgorithms\OwnerShip\container\Tree\Tree.h"
#include "..\StructAndAlgorithms\Iterator\Iterator.h"

void TestQueue1(void)
{
    Queue& queue1 = *new QueueAsLinkedList;
    queue1.Enqueue(*new Int(10));
    queue1.Enqueue(*new Int(20));
    queue1.Enqueue(*new Int(40));  
    cout << queue1 << endl;

    Queue& queue2 = *new QueueAsLinkedList;
    queue2.Enqueue(*new Int(10));
    queue2.Enqueue(*new Int(30));
    queue2.Enqueue(*new Int(30));
    cout << queue2 << endl;

    if(queue1 == queue2)
    {
        cout << "queue1 == queue2" << endl;
    }
    else if(queue1 < queue2)
    {
        cout << "queue1 < queue2" << endl;
    }
    else
    {
        cout << "queue1 > queue2" << endl;
    }

    delete &queue1;
    delete &queue2;
}

void TestBinaryHeap()
{
    BinaryHeap heap(100);
    heap.Enqueue(*new Int(10));
    heap.Enqueue(*new Int(12));
    heap.Enqueue(*new Int(5));
    heap.Enqueue(*new Int(20));
    heap.Enqueue(*new Int(22));
    heap.Enqueue(*new Int(25));
    
    while(!heap.IsEmpty())
    {
        Int* pInt = dynamic_cast<Int*>(&heap.DequeueMin());
        cout << *pInt << "  ";
        delete pInt;
    }
    cout << endl << heap << endl << heap.Count();
}

void TestLeftistHeap()
{
    LeftistHeap& heap = *new LeftistHeap;
    heap.Enqueue(*new Int(10));
    heap.Enqueue(*new Int(12));
    heap.Enqueue(*new Int(5));
    cout << heap << endl << "count is:" << heap.Count();
    cout << endl;

    LeftistHeap &heap1 = *new LeftistHeap;
    heap1.Enqueue(*new Int(20));
    heap1.Enqueue(*new Int(22));
    heap1.Enqueue(*new Int(25));

    heap.Merge(heap1);
    cout << heap << endl << "count is:" << heap.Count();
    cout << endl;

    while(!heap.IsEmpty())
    {
        Int* pInt = dynamic_cast<Int*>(&heap.DequeueMin());
        cout << *pInt << "  ";
        delete pInt;
    }
}

void TestBinomialTree()
{
    BinomialQueue& heap = *new BinomialQueue;
    heap.Enqueue(*new Int(5));
    heap.Enqueue(*new Int(10));
    heap.Enqueue(*new Int(12));
    cout << heap << endl << "count is:" << heap.Count();
    cout << endl;

    BinomialQueue &heap1 = *new BinomialQueue;
    heap1.Enqueue(*new Int(20));
    heap1.Enqueue(*new Int(22));
    heap1.Enqueue(*new Int(25));
    cout << heap1 << endl << "count is:" << heap1.Count();
    cout << endl;

    heap.Merge(heap1);
    cout << heap << endl << "count is:" << heap.Count();
    cout << endl;

    while(!heap.IsEmpty())
    {
        Object& Object = heap.DequeueMin();
        cout << Object << "  ";
        delete &Object;
    }
}
#endif //_TESTQUEUE_H_