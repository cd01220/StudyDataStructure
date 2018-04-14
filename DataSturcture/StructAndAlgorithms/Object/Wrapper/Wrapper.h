#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <string>
#include "..\Object.h"
/*********************************************************
*���ߣ� liuhao
*˵��: �ο���81ҳ��8�У�Ҫ���������ʵ�ֵ�::Compare()��::Hash()��ԭ��ʵ�֡�
*      �Ƚ�����ֵ�Ĵ�С��
*����ֵ  : С�� -1; ���� 1; ���� 0
*********************************************************/
template <class T>
int Compare(T lPara, T rPara)
{
	if(lPara < rPara)
		{return -1;}
	if(lPara == rPara)
        {return 0;}
    return 1;
}

//////////////////////////////////////////////////////////////////////////////
//	Class: Wrapper
//////////////////////////////////////////////////////////////////////////////
template <class T>
class Wrapper : public Object
{
protected:
    T datum;

    int CompareTo (Object const&) const;
public:
    Wrapper ();
	~Wrapper (){}
    Wrapper (T const&);
    Wrapper& operator = (T const&);
    operator T const& () const;
    HashValue Hash () const;
    void Put (ostream&) const;
};

template <class T>
Wrapper<T>::Wrapper () :
    datum ()
    {}

template <class T>
Wrapper<T>::Wrapper (T const& d) :
    datum (d)
    {}

template <class T>
Wrapper<T>& Wrapper<T>::operator = (T const& d)
{
    datum = d;
    return *this;
}

template <class T>
Wrapper<T>::operator T const& () const
{ 
	return datum; 
}

template <class T>
HashValue Wrapper<T>::Hash() const
{ 
	return ::Hash (datum);  
}

template <class T>
int Wrapper<T>::CompareTo (Object const& obj) const
{
    Wrapper<T> const& arg =	dynamic_cast<Wrapper<T> const&> (obj);
    return ::Compare (datum, arg.datum);
}

template <class T>
void Wrapper<T>::Put (ostream& s) const
{ 
    s << datum; 
}

typedef Wrapper<int> Int;
typedef Wrapper<char> Char;
typedef Wrapper<double> Double;
typedef Wrapper<std::string> String;

#endif  //_WRAPPER_H_