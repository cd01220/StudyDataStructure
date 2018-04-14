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

//˵�������������Ż�ֻ����ǰ���������ŵĵı��ʽ��
//   ��:2+3*4��(2+3*4)�� ��������InfixToInfix���á�
//������stack ���ݰ����������оٵı��ʽ��
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
    //����")"ʱ�� ѭ��ȡ����ջ������ݲ�����һ������ֱ����������Ӧ��"("��
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
    } //ջ��Ϊ�գ���ջ��Ԫ�ز�Ϊ"("��

    //�������е��ˣ�����������"(",")", �Ӷ�ջ��ȡ���ϴλ�û�����Ķ����"(",
    //ͬʱ����ջ���Ĳ�����������ȼ���־����ʾ��ǰ����������һ�������С�
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

//��������������׺���ʽ����һ�ñ��ʽ��, ����ӡ������
void InfixToInfix()
{
    char acExp[] = "(2+3)*4+(2+3)*4-(2+3)*4";
    Stack& stack = *new StackAsLinkedList ();

    int i = 0;
    char c;
    //��һ��ѭ������������е����š�
    while ((c = acExp[i++]) != 0)
    {
        stack.Push (*new ExpressionTree (c));
        if (')' == c)
        {	        
            ExpressionInStack(stack);
        }        
    }//while ((c = acExp[i++]) != 0)

    //��һ���Ѿ����������е����ţ����ѷ����˶�ջ�� ���ڰѶ�ջ����������ȡ��������
    //��������һ������
    ExpressionInStack(stack);
   
    ExpressionTree& result =
	    dynamic_cast<ExpressionTree&> (stack.Pop ());
    InfixVisitor visitor;
    result.DepthFirstTraversal (visitor);

    cout << endl << result;
    delete &result;
    delete &stack;
}

