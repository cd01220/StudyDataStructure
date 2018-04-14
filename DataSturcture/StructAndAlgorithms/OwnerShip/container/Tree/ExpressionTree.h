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

//随书代码的InfixVisitor会导制遍历树时打出多余的括号， 根书书231页，
//习题9.6的要求， 修改此访问者类。 2005-11-25
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
    //算法描述：当前类为中序访问，但PreVisit()为先序访问函数，只用于打印左括
    //号，只有在后访问到的运算符优先级比上一个运算符高时，才需要打印左括号。
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
    //算法描述：当前类为中序访问，但PostVisit()为后序访问函数，只用于打印右括
    //号，只有在先序访问中后访问到的运算符优先级比上一个运算符高时，才需要打
    //印右括号。
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