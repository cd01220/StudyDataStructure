#ifndef _APPLY_PRIORITYQUEUE_H_
#define _APPLY_PRIORITYQUEUE_H_

#include ".\StructAndAlgorithms\OwnerShip\Association.h"

typedef double time;
class Event : public Association
{
public:
    enum type
    {
	    arrival, departure
    };
    typedef Wrapper<type> Type;
    typedef Wrapper<time> Time;

    Event (type typ, time tim) : Association (*new Time (tim), *new Type (typ)) 
    {}

    Time& Key () const
	{ 
        return dynamic_cast<Time&> (Association::Key ()); 
    }

    Type& Value () const
	{ 
        return dynamic_cast<Type&> (Association::Value()); 
    }
};

#endif