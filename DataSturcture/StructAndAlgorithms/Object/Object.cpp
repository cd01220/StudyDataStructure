#include <math.h>
#include <typeinfo>
#include <string>

#include "Object.h" 

Object::~Object ()
    {}

bool Object::IsNull () const
    { return false; }

int Object::Compare (Object const& object) const
{
    if (typeid (*this) == typeid (object))
		return CompareTo (object);
    else if (typeid (*this).before (typeid (object)))
		return -1;
    else
		return 1;
}

//Object 的各种比较操作符。
//bool operator == (Object const& left, Object const& right)
//{ 
//    return left.Compare (right) == 0; 
//}

//	各种类型的哈希算法。
//////////////////////////////////////////////////////////////////////////////
HashValue Hash(char c)
    { return abs (c); }

HashValue Hash(int i)
    { return abs (i); }

HashValue Hash(unsigned int i)
{return i;}

HashValue Hash(double d)
{
	if (d == 0)
		return 0;
    else
    {
		int exponent;
		double mantissa = frexp (d, &exponent);
		return static_cast<HashValue>((2 * fabs (mantissa) - 1) * ~0U);
    }
}

unsigned int const shift = 6;
HashValue const mask = ~0U << (sizeof(HashValue) * 8 - shift);
HashValue Hash (string const& s)
{
    HashValue result = 0;
    for (unsigned int i = 0; s [i] != 0; ++i)
    {   
        result = (result & mask) ^ (result << shift) ^ s [i];
    }
    return result;
}
