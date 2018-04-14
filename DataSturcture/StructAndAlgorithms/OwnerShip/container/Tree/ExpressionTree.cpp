#include ".\ExpressionTree.h"
#include ".\StructAndAlgorithms\OwnerShip\container\Stack\StackAsLinkedList.h"
#include <crtdbg.h>

void PostfixToInfix ()
{
    char c;
    Stack& stack = *new StackAsLinkedList ();

    while (cin >> c, c != '=')
    {
        if (isdigit (c) || isalpha (c))
	        stack.Push (*new ExpressionTree (c));
	    else if (c == '+' || c == '-' || c == '*' || c == '/')
	    {
	        ExpressionTree& result = *new ExpressionTree (c);
	        result.AttachRight ( dynamic_cast<ExpressionTree&> (stack.Pop ()));
	        result.AttachLeft (dynamic_cast<ExpressionTree&> (stack.Pop ()));
	        stack.Push (result);
	    }
    }
    ExpressionTree& result =
	    dynamic_cast<ExpressionTree&> (stack.Pop ());
    InfixVisitor visitor;
    result.DepthFirstTraversal (visitor);

    cout << endl;
    delete &result;
    delete &stack;
}

//说明：处理不带括号或只在最前和最后带括号的的表达式，
//   如:2+3*4或(2+3*4)， 本函数被InfixToInfix调用。
//参数：stack 内容包括了上面列举的表达式。
void ExpressionInStack(Stack& stack)
{
    int iCurLevel = 0;
    int iLastLevel = 0;
    bool bIsFirst = true;
    if(dynamic_cast<ExpressionTree &>(stack.Top()).Key() == Char(')'))
    {
        stack.Pop();
    }

    ExpressionTree* pTreeLastTree = dynamic_cast<ExpressionTree *>(&stack.Pop());
    //cout << pTreeLastTree->Key() << endl;
    //读到")"时， 循环取出堆栈里的内容并生成一棵树，直到读到了相应的"("。
    while(!stack.IsEmpty()
        && dynamic_cast<ExpressionTree &>(stack.Top()).Key() != Char('('))
    {
        ExpressionTree &treeOperator = dynamic_cast<ExpressionTree &>(stack.Pop());
        ExpressionTree &treeOperand = dynamic_cast<ExpressionTree &>(stack.Pop());        
        //cout << treeOperator.Key() << endl;
        //cout << treeOperand.Key() << endl;

        if(treeOperator.Key() == Char('+') || treeOperator.Key() == Char('-'))
        {  iCurLevel = 1;}
        else if(treeOperator.Key() == Char('*') || treeOperator.Key() == Char('/'))
        {  iCurLevel = 2;}
        else
        {
            _ASSERT(false);
        }

        treeOperator.AttachLeft(treeOperand);
        if(iCurLevel >= iLastLevel)
        {
            if(bIsFirst)
            {
                treeOperator.AttachRight(*pTreeLastTree);
                pTreeLastTree = &treeOperator; 
                bIsFirst = false;
            }
            else
            {
                treeOperator.AttachRight(pTreeLastTree->DetachLeft());
                pTreeLastTree->AttachLeft(treeOperator);
            }
        }
        else
        {   
            treeOperator.AttachRight(*pTreeLastTree);
            pTreeLastTree = &treeOperator;   
        }
        iLastLevel = iCurLevel;
    } //栈不为空，且栈顶元素不为"("。

    //程序运行到此，如果曾处理过"(",")", 从堆栈中取出上次还没丢掉的多余的"(",
    //同时，给栈顶的操作符添加优先级标志，表示当前树内容来自一个括号中。
    if(!stack.IsEmpty()
        && dynamic_cast<ExpressionTree &>(stack.Top()).Key() == Char('('))
    {
        stack.Pop();
        //Char &charOperator = (Char &)pTreeLastTree->Key();
        //charOperator = Char('a');
        //cout << *pTreeLastTree;
    }
    
    stack.Push(*pTreeLastTree);
}

//功能描述：从中缀表达式构造一棵表达式树, 并打印出来。
void InfixToInfix()
{
    char acExp[] = "(2+3)*4+(2+3)*4-(2+3)*4";
    Stack& stack = *new StackAsLinkedList ();

    int i = 0;
    char c;
    //第一次循环，处理掉所有的括号。
    while ((c = acExp[i++]) != 0)
    {
        stack.Push (*new ExpressionTree (c));
        if (')' == c)
        {	        
            ExpressionInStack(stack);
        }        
    }//while ((c = acExp[i++]) != 0)

    //上一步已经处理了所有的括号，并已放入了堆栈， 现在把堆栈中所有内容取出来，并
    //用来生成一棵树。
    ExpressionInStack(stack);
   
    ExpressionTree& result =
	    dynamic_cast<ExpressionTree&> (stack.Pop ());
    InfixVisitor visitor;
    result.DepthFirstTraversal (visitor);

    cout << endl << result;
    delete &result;
    delete &stack;
}

