#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

//////////////////////////////////////////////////////////////////////////////
//	Class: PriorityQueuePrintVisitor
//////////////////////////////////////////////////////////////////////////////
template <class T>
class PriorityQueuePrintVisitor : public Visitor<T>
{
private:
    ostream& theOs;
    bool comma;

public:
    PriorityQueuePrintVisitor(ostream& os): theOs(os), comma(false)
	{}

    void Visit(T& object)
    {
        if (comma)
        {
            theOs << ", ";
        }
        theOs << object;
        comma = true;
    }
};

template<class T>
class PriorityQueue
{
protected:
    unsigned int count;
    
    PriorityQueue();

public:    
    virtual void Enqueue(T) = 0;
    virtual T& FindMin() = 0;
    virtual T DequeueMin() = 0;

    virtual void Accept (Visitor<T>&) = 0;
    virtual void Put (ostream&);
};

template <class T>
inline ostream& operator << (ostream& os, PriorityQueue<T>& queue)
{ 
    queue.Put(os); 
    return os; 
}

template <class T>
PriorityQueue<T>::PriorityQueue() :
    count(0)
{
}

template <class T>
void PriorityQueue<T>::Put(ostream& os)
{
    PriorityQueuePrintVisitor<T> visitor(os);

    os << typeid (*this).name() << " {";
    Accept (visitor);
    os << "}";
}

template<class T>
class MergeablePriorityQueue : public virtual PriorityQueue<T>
{
public:
    virtual void Merge(MergeablePriorityQueue&) = 0;
};


#endif