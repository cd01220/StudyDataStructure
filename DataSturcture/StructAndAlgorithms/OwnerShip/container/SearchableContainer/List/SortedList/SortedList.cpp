#include "SortedList.h"

//SortedListAsArray��̳���class SortedList, class ListAsArray��������ĸ��඼
//�˲�������/�������Ķ��壬Ϊ�˱���C4250���棬 �ڴ���ʾ���庯����ʵ�֡�
Object& SortedListAsArray::operator [] (unsigned int offset) const
{
    return ListAsArray::operator [](offset);
}
//Ϊ�˱���C4250���棬 �ڴ���ʾ���庯����ʵ�֡�
Object& SortedListAsArray::operator [] (Position const& arg) const
{
    return ListAsArray::operator [](arg);
}
//Ϊ�˱���C4250���棬 �ڴ���ʾ���庯����ʵ�֡�
void SortedListAsArray::Purge()
{ 
    ListAsArray::Purge(); 
}
//Ϊ�˱���C4250���棬 �ڴ���ʾ���庯����ʵ�֡�
void SortedListAsArray::Accept(Visitor& visitor) const
{
    ListAsArray::Accept(visitor);
}
//Ϊ�˱���C4250���棬 �ڴ���ʾ���庯����ʵ�֡�
Iterator& SortedListAsArray::NewIterator() const
{
    return ListAsArray::NewIterator();
}
bool SortedListAsArray::IsMember (Object const& object) const
{
    return ListAsArray::IsMember(object);
}
//Ϊ�˱���C4250���棬 �ڴ���ʾ���庯����ʵ�֡�
void SortedListAsArray::Withdraw (Position const& arg)
{
    ListAsArray::Withdraw (arg);
}

void SortedListAsArray::Insert (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("list is full");
    unsigned int i = count;
    while (i > 0 && *array [i - 1U] > object)
    {
	    array [i] = array [i - 1U];
	    --i;
    }
    array [i] = &object;
    ++count;
}

SortedListAsArray::SortedListAsArray(unsigned int size) :
        ListAsArray(size)
{
}

unsigned int SortedListAsArray::FindOffset (
    Object const& object) const
{
    int left = 0;
    int right = count - 1;

    while (left <= right)
    {
	    int const middle = (left + right) / 2;

	    if (object > *array [middle])
	        left = middle + 1;
	    else if (object < *array [middle])
	        right = middle - 1;
	    else
	        return middle;
    }
    return count;
}

Object& SortedListAsArray::Find (Object const& object) const
{
    unsigned int const offset = FindOffset (object);

    if (offset < count)
	    return *array [offset];
    else
	    return NullObject::Instance ();
}

Position& SortedListAsArray::FindPosition (
    Object const& object) const
{            
    //modified by liuhao, ����CD�е�Դ��ͨ�������룬δ�޸�ǰ�������ģ�
    //Pos& result = *new Pos (*this);  
    Pos& result = *new Pos (*this, 0);  
    result.offset = FindOffset (object);
    return result;
}

void SortedListAsArray::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("list is empty");

    unsigned int const offset = FindOffset (object);

    if (offset == count)
	throw invalid_argument ("object not found");

    for (unsigned int i = offset; i < count - 1U; ++i)
	array [i] = array [i + 1];
    --count;
}