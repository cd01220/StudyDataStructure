#ifndef _TESTSTACKASLIST_H_
#define _TESTSTACKASLIST_H_

#include "..\StructAndAlgorithms\OwnerShip\container\Stack\StackAsArray.h"
void TestStack()
{
	StackAsArray stk1(10);
    //StackAsLinkedList stk1;
	stk1.Push(*new Int(3));
	stk1.Push(*new Int(4));
	stk1.Push(*new Int(5));

    StackAsArray stk2(10);
    //StackAsLinkedList stk2;
	stk2.Push(*new Int(3));
	stk2.Push(*new Int(4));
    stk2.Push(*new Int(5));

	cout << stk1 << endl;
    cout << stk2 << endl;

    if(stk1 == stk2)
    {
        cout << "stk1 == stk2" << endl;
    }
    else if(stk1 < stk2)
    {
        cout << "stk1 < stk2" << endl;
    }
    else
    {
        cout << "stk1 > stk2" << endl;
    }
}

/* 栈应用于----一位PRN计算器*/
void RPNCalculator (Stack& stack)
{
    char c;
    while (cin >> c, !cin.eof ())
    {
		if (isdigit (c))
			stack.Push (*new Int (c - '0'));
		else if (c == '+')
		{
			Int& arg2 = dynamic_cast<Int&> (stack.Pop ());
			Int& arg1 = dynamic_cast<Int&> (stack.Pop ());
			stack.Push (*new Int (arg1 + arg2));
			delete &arg1;
			delete &arg2;
		}
		else if (c == '*')
		{
			Int& arg2 = dynamic_cast<Int&> (stack.Pop ());
			Int& arg1 = dynamic_cast<Int&> (stack.Pop ());
			stack.Push (*new Int (arg1 * arg2));
			delete &arg1;
			delete &arg2;
		}
		else if (c == '=')
		{
			Int& arg = dynamic_cast<Int&> (stack.Pop ());
			cout << arg << endl;
			delete &arg;
			if(stack.Count() != 0)
			{
				stack.Purge();
				cout << "err";
			}
		}
    }
}





#endif //_TESTSTACKASLIST_H_