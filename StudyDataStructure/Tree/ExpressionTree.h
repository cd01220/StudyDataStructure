#ifndef _EXPRESSION_TREE_H_
#define _EXPRESSION_TREE_H_

#include "BinaryTree.h"

class ExpressionTree : public BinaryTree<char>
{
public:
    ExpressionTree(char c) : BinaryTree(c) 
    {}
};

//随书代码的InfixVisitor会导制遍历树时打出多余的括号， 根书书231页，
//习题9.6的要求， 修改此访问者类。 2005-11-25
class InfixVisitor : public PrePostVisitor<char>
{
private:
    stack<int> priorityStack;

public:
    InfixVisitor()
    { }

    ~InfixVisitor()
    {
    }

    //modified by liuhao 2005-11-25.
    //算法描述：当前类为中序访问，但PreVisit()为先序访问函数，只用于打印左括
    //号，只有在后访问到的运算符优先级比上一个运算符高时，才需要打印左括号。
    void PreVisit(char& c)
	{ 
        if(c == '+' || c == '-')
        {
            if(!priorityStack.empty() && priorityStack.top() == 2)
            {
                cout << "("; 
            }
            priorityStack.push(1);            
        }
        else if(c == '*' || c == '/')
        {            
            priorityStack.push(2);
        }        
    }

    void Visit(char& c)
	{ 
        cout << c; 
    }

    //modified by liuhao 2005-11-25.
    //算法描述：当前类为中序访问，但PostVisit()为后序访问函数，只用于打印右括
    //号，只有在先序访问中后访问到的运算符优先级比上一个运算符高时，才需要打
    //印右括号。
    void PostVisit(char& c)
	{ 
        if(c == '+' || c == '-')
        {
            priorityStack.pop();
            if(!priorityStack.empty() && priorityStack.top() == 2)
            {
                cout << ")";  
            }                       
        }
        else if(c == '*' || c == '/')
        {            
            priorityStack.pop();
        }           
    }
};

/* 从后缀表达式创建ExpressionTree */
ExpressionTree* CreateTreeFromPostExpression(char* expression)
{
    char c;
    stack<ExpressionTree*> stack;

    for(c = *expression; c != '\0'; c = *++expression)
    {
        if (isdigit (c) || isalpha (c))
	        stack.push (new ExpressionTree(c));
	    else if (c == '+' || c == '-' || c == '*' || c == '/')
	    {
	        ExpressionTree* result = new ExpressionTree(c);
	        result->AttachRight(stack.top());
            stack.pop();

	        result->AttachLeft (stack.top());
            stack.pop();

	        stack.push(result);
	    }
    }
    ExpressionTree* result = stack.top();
    stack.pop();

    return result;
}

static unsigned int Priority(char c)
{
    unsigned int ret;
    switch (c)
    {
    case '+':
    case '-':
        ret = 0;
        break;

    case '*':
    case '/':
        ret = 1;
        break;

    default:
        throw out_of_range ("invalid operator.");
    }
    return ret;
}

/* 从中缀表达式创建ExpressionTree */
ExpressionTree* CreateTreeFromInExpression(char* expression)
{    
    ExpressionTree* tree;
    stack<ExpressionTree*> operatorStack;
    stack<ExpressionTree*> operandTree;
    
    for(char c = *expression; c != '\0'; c = *++expression)
    {	        
        switch(c)
        {
        case '(':
            operatorStack.push(new ExpressionTree(c));
            break;

        case ')':
            while (operatorStack.top()->Key() != '(')
            {
                tree = operatorStack.top();
                operatorStack.pop();

                tree->AttachRight(operandTree.top());
                operandTree.pop();

                tree->AttachLeft(operandTree.top());
                operandTree.pop();

                operandTree.push(tree);
            }
            operatorStack.pop();
            break;
     
        case '+':
        case '-':
        case '*':
        case '/':
            if (!operatorStack.empty() 
                && (operatorStack.top()->Key() == '+' 
                    || operatorStack.top()->Key() == '-' 
                    || operatorStack.top()->Key() == '*'
                    || operatorStack.top()->Key() == '/')
                && Priority(c) <= Priority(operatorStack.top()->Key()))
            {
                tree = operatorStack.top();
                operatorStack.pop();

                tree->AttachRight(operandTree.top());
                operandTree.pop();

                tree->AttachLeft(operandTree.top());
                operandTree.pop();

                operandTree.push(tree);
            }

            operatorStack.push(new ExpressionTree(c));
            break;

        default:   /* number */
            operandTree.push(new ExpressionTree(c));
        }
    } 

    while(!operatorStack.empty())
    {
        tree = operatorStack.top();
        operatorStack.pop();

        tree->AttachRight(operandTree.top());
        operandTree.pop();

        tree->AttachLeft(operandTree.top());
        operandTree.pop();

        operandTree.push(tree);
    }

    tree = operandTree.top();
    operandTree.pop();

    return tree;
}

#endif //_EXPRESSION_TREE_H_