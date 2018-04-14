#ifndef _EXPRESSION_TREE_H_
#define _EXPRESSION_TREE_H_

#include ".\BinaryTree.h"
#include ".\StructAndAlgorithms\OwnerShip\container\Stack\StackAsLinkedList.h"

class ExpressionTree : public BinaryTree
{
public:
    ExpressionTree (char c) : BinaryTree (*new Char (c)) 
    {}
};

//��������InfixVisitor�ᵼ�Ʊ�����ʱ�����������ţ� ������231ҳ��
//ϰ��9.6��Ҫ�� �޸Ĵ˷������ࡣ 2005-11-25
class InfixVisitor : public PrePostVisitor
{
private:
    Stack& stack;
public:
    InfixVisitor() : stack(*new StackAsLinkedList ())
    { }
    ~InfixVisitor()
    {delete &stack;}

    //modified by liuhao 2005-11-25.
    //�㷨��������ǰ��Ϊ������ʣ���PreVisit()Ϊ������ʺ�����ֻ���ڴ�ӡ����
    //�ţ�ֻ���ں���ʵ�����������ȼ�����һ���������ʱ������Ҫ��ӡ�����š�
    void PreVisit (Object& object)
	{ 
        Char &c = (Char &)object;
        if(c == Char('+') || c == Char('-'))
        {
            if(!stack.IsEmpty() && stack.Top() == Int(2))
            {
                cout << "("; 
            }
            stack.Push(*new Int(1));            
        }else if(c == Char('*') || c == Char('/'))
        {            
            stack.Push(*new Int(2));
        }        
    }

    void Visit (Object& object)
	{ cout << object; }

    //modified by liuhao 2005-11-25.
    //�㷨��������ǰ��Ϊ������ʣ���PostVisit()Ϊ������ʺ�����ֻ���ڴ�ӡ����
    //�ţ�ֻ������������к���ʵ�����������ȼ�����һ���������ʱ������Ҫ��
    //ӡ�����š�
    void PostVisit (Object& object)
	{ 
        Char &c = (Char &)object;
        if(c == Char('+') || c == Char('-'))
        {
            stack.Pop();
            if(!stack.IsEmpty() && stack.Top() == Int(2))
            {
                cout << ")";  
            }
                       
        }else if(c == Char('*') || c == Char('/'))
        {            
            stack.Pop();
        }           
    }
};

void PostfixToInfix ();
void InfixToInfix();

#endif //_EXPRESSION_TREE_H_