
class Linklist
{
public:
    Linklist(int value) : next(NULL), value(value)
    {   }

public:
    Linklist* next;
    int value;
};

static Linklist* MakeLinklist()
{
    int array[] = {1,2,3,4,5,6,7};
    size_t elements = sizeof(array) / sizeof(int);
    size_t i;

    Linklist* header;
    Linklist *curr, *prev;
    
    for (i = 0; i < elements; ++i)
    {
        curr = new Linklist(array[i]);
        if (i == 0)
        {
            header = curr;
        }
        else
        {
            prev->next = curr;
        }

        prev = curr;
    }
    return header;
}

static void PrintLinklist(Linklist* head)
{
    Linklist* curr;
    for (curr = head; curr != NULL; curr = curr->next)
    {
        if (curr != head)
            cout << ", ";

        cout << curr->value;
    }
    cout << endl;
}

/* 单链表反转 */
void ReverseLinkList()
{
    Linklist* head = MakeLinklist();
    PrintLinklist(head);

    Linklist* prev = NULL;
    Linklist* next;
    while (head != NULL)
    {
        next = head->next;
        head->next = prev;

        prev = head;
        head = next;
    }

    head = prev;
    PrintLinklist(head);
}

/* 找出单链表的倒数第4个元素 */
void FindTheLastBut4()
{
    Linklist* next4 = MakeLinklist();
    Linklist* curr = next4;
    PrintLinklist(next4);

    int i;
    for (i = 0; i < 4 && next4 != NULL; ++i)
        next4 = next4->next;

    if (next4 == NULL)
    {
        cout << "NULL" << endl;
        return;
    }

    while (next4 != NULL)
    {
        curr = curr->next;
        next4 = next4->next;
    }

    cout << curr->value << endl;
}

/* 找出单链表的中间元素 */
void FindTheMiddle()
{
    Linklist* head = MakeLinklist();
    PrintLinklist(head);

    Linklist* middle = head;
    while (head != NULL && head->next != NULL)
    {
        head = head->next->next;

        middle = middle->next;
    }

    cout << middle->value << endl;
}

/* 一个单链表，很长，遍历一遍很慢，我们仅知道一个指向某节点的指针curr，而我们又想删除这个节点。*/
Linklist* DeleteCurrenNode(Linklist* node)
{
    Linklist* ret;

    if (node->next != NULL)
    {
        ret = node->next;
        node->value = node->next->value;
        node->next = node->next->next;
    }
    else
    {
        /* node 为链表的最后一个节点, 此时我们只能遍历整个链表找出倒数第二个节点.... */
    }

    return ret;
}

Linklist* MakeLoopLinklist()
{
    Linklist* head = MakeLinklist();
    Linklist *curr, *node3;

    for (curr = head; curr->next != NULL; curr = curr->next)
    {
        if (curr->value == 3)
            node3 = curr;
    }

    curr->next = node3;

    return head;
}

/* 判断单链表是否有环？如何找到环的“起始”点？如何知道环的长度？ */
void CheckLoop(Linklist* head)
{
    int step1, step2;
    Linklist *first = head;
    Linklist *sec = head;
    step1 = 0;
    step2 = 0;
    while (first->next != NULL && sec->next != NULL)
    {
        first = first->next->next;
        sec = sec->next;
        if (first == sec)
            break;
    }

    int length = 0;
    if (first != first->next)
    {
        length = 1;
        for (first = first->next; first != sec; first = first->next)
        {
            ++length;
        }
    }

    cout << sec->value << ", loop length = " << length << endl;
}

/* 单链表排序 
   算法思想： 和数组排序相比， 单链表最大的问题是不能通过数组下标访问当前节点的前一个节点。
   但是我们可以对数组排序的算法做一些改动，来完成排序。 

   假设我们使用冒泡算法， 冒泡算法的外循环是从右到左， 用于计算内层循环的边界， 所以在不申
   请额外空间的情况下， 单链表排序不适合使用冒泡算法。

   本例中我们使用插入排序的算法。
 */
void SortLink()
{
    Linklist* head = MakeLinklist();


    PrintLinklist(head);
}

void MakeStack(stack<int>& intStack)
{
    const int N = 5;
    for (int i = 1; i <= N; ++i)
    {
        intStack.push(i);
    }
}

void PrintStack(stack<int>& intStack)
{
    while (!intStack.empty())
    {
        cout << intStack.top();
        intStack.pop();
        if (!intStack.empty())
            cout << ", ";
    }
    cout << endl;
}

/* 递归反转一个栈，要求不得重新申请一个同样的栈 
   算法思想: 每一次递归都记录当前的top, 和interimTop 值, 最后反序将其压入堆栈中. 有点类似于
             冒泡算法, 每次都将当前的top 放栈底.
 */
static void ReverseStackRecursively(stack<int> &destStack, int deep, const int &top)  
{  
    if (deep == 0)  
    {  
        destStack.push(top);  
        return ;  
    }  
    int interimTop = destStack.top();  
    destStack.pop();  
    ReverseStackRecursively(destStack, deep - 1, top);  
    destStack.push(interimTop);  
}  
  
void ReverseStackRecursively(stack<int> &destStack)  
{  
    if (destStack.size() == 0)
        return;

    for (size_t i = 0; i < destStack.size(); ++i)  
    {  
        int top = destStack.top();  
        destStack.pop();  
        int deep = destStack.size() - i;  
        ReverseStackRecursively(destStack, deep, top);  
    }  
}

/*  如何用一个数组实现两个栈 
    算法思想:  第一个栈A从最左向右增长, 第二个栈从最右向左增长
 */
class NewStack
{
public:
    void pushA(int value);
    void pushB(int value);
};

/* 设计一个算法，找出二叉树上任意两个节点的最近共同父结点，复杂度如果是O(n2)则不得分。
   算法1：做一个容器，我们在遍历二叉树寻找节点的同时，把从根到节点的路径扔进去（两个节点就是两
          个容器）。 由于根节点最后一个被扔进去，但我们接下来又需要第一个就能访问到它——后进先
          出，所以这个容器是一个栈。 时间复杂度O(N)，空间复杂度O(N)。

   Example:
    BinaryTree<int> tree(1);
    tree.AttachLeft(new BinaryTree<int>(2));
    tree.AttachRight(new BinaryTree<int>(3));

    tree.Left().AttachLeft(new BinaryTree<int>(4));
    tree.Left().AttachRight(new BinaryTree<int>(5));
    
    BinaryTree<int>* result = FindParentNode(&tree, &tree.Left().Left(), &tree.Left().Right());
 */
#include "Tree/BinaryTree.h"

static bool GetPositionByNode(BinaryTree<int>* root, BinaryTree<int>* node, stack<BinaryTree<int>*>& pathStack)
{
    if (root == node)
    {
        pathStack.push(root);
        return true;
    }

    if (!root->Left().IsEmpty() && GetPositionByNode(&root->Left(), node, pathStack))
    {
        pathStack.push(root);
        return true;
    }

    if (!root->Right().IsEmpty() && GetPositionByNode(&root->Right(), node, pathStack))
    {
        pathStack.push(root);
        return true;
    }

    return false;
}

BinaryTree<int>* FindParentNode(BinaryTree<int>* root, BinaryTree<int>* node1, BinaryTree<int>* node2)
{
    stack<BinaryTree<int>*> stack1;
    GetPositionByNode(root, node1, stack1);

    stack<BinaryTree<int>*> stack2;
    GetPositionByNode(root, node2, stack2);

    BinaryTree<int>* tempNode = NULL;
    while (stack1.top() == stack2.top())
    {
        tempNode = stack1.top();

        stack1.pop();
        stack2.pop();
    }
    return tempNode;
}

/* 如何不用递归实现二叉树的前序/后序/中序遍历？ 
   算法思想：三种算法的思想都是让root的Left的Left的Left全都入栈。所以第一个while循环的逻辑，都是相同的。
   下面详细分析第2个while循环，这是一个出栈动作，只要栈不为空，就始终要弹出栈顶元素，由于我们之前入栈的
   都是Left节点，所以每次在出栈的时候，我们都要考虑Right节点是否存在。因为前序/后序/中序遍历顺序的不同，
   所以在具体的实现上有略为区别。

    Example:
    BinaryTree<int> tree(1);
    tree.AttachLeft(new BinaryTree<int>(2));
    tree.AttachRight(new BinaryTree<int>(3));

    tree.Left().AttachLeft(new BinaryTree<int>(4));
    tree.Left().AttachRight(new BinaryTree<int>(5));
    tree.Right().AttachRight(new BinaryTree<int>(6));

    PreOrderAccess(tree);
 */
void PreOrderAccess(BinaryTree<int>* root)
{
    TreePrintVisitor<int> visitor(cout);
    stack<BinaryTree<int>*> treeStack;
    treeStack.push(root);

    while (!treeStack.empty())
    {
        BinaryTree<int>* top = treeStack.top();
        treeStack.pop();

        if (!top->Right().IsEmpty())
        {
            treeStack.push(&top->Right());
        }

        if (!top->Left().IsEmpty())
        {
            treeStack.push(&top->Left());
        }

        visitor.Visit(top->Key());
    }
}

void InOrderAccess(BinaryTree<int>* root)
{
    TreePrintVisitor<int> visitor(cout);
    stack<BinaryTree<int>*> treeStack;

    treeStack.push(root);
    BinaryTree<int>* top = root;

    while (!treeStack.empty())
    {
        while (top != NULL && !top->Left().IsEmpty())
        {
            top = &top->Left();
            treeStack.push(top);
        }

        top = treeStack.top();
        treeStack.pop();
        visitor.Visit(top->Key());
        
        if (!top->Right().IsEmpty())
        {
            top = &top->Right();
            treeStack.push(top);
        }
        else 
            top = NULL;
    }
}

void PostOrderAccess(BinaryTree<int>* root)
{
    TreePrintVisitor<int> visitor(cout);
    stack<BinaryTree<int>*> treeStack;

    BinaryTree<int> *top = root;
    BinaryTree<int> *previous = NULL;    //previous表示最近一次访问过的结点

    treeStack.push(top);
    while (top != NULL || !treeStack.empty())
    {
        //沿着左孩子方向走到最左下 。
        while (top != NULL && !top->Left().IsEmpty())
        {
            top = &top->Left();
            treeStack.push(top);
        }
        
        top = treeStack.top();    
        if (top->Right().IsEmpty() || &top->Right() == previous)
        {
            //没有右孩子， 或者其右孩子刚刚被访问过
            treeStack.pop();
            visitor.Visit(top->Key());
            previous = top;
            top = NULL;
        }
        else
        {
			//有右孩子, 访问右孩子.
            top = &top->Right();
            treeStack.push(top);
        }
    }
}

/* 在二叉树中找出和为某一值的所有路径 
	Example:
    BinaryTree<int> tree(1);
    tree.AttachLeft(new BinaryTree<int>(3));
    tree.AttachRight(new BinaryTree<int>(2));

    tree.Left().AttachLeft(new BinaryTree<int>(4));
    tree.Left().AttachRight(new BinaryTree<int>(5));
    tree.Right().AttachRight(new BinaryTree<int>(6));

    FundAllPaths(tree, 9);   //Result: {1, 3, 5}, {1, 2, 6}
 */
template <class T>
class CountVisitor : public PrePostVisitor<T>
{
private:
    int count;
	int currCount;
	bool isDone;
	stack<T> result;

public:
    CountVisitor(T count): count(count), currCount(0), isDone(false)
	{}

	void PreVisit (T& object) 
	{
		result.push(object);
		currCount += object;
		if (currCount == count)
		{
			isDone = true;
			Print();
		}
	}
    
    void Visit(T&)
    {
    }

	void PostVisit (T& object) 
	{
		result.pop();
		currCount -= object;
	}

	void Print()
	{
		static bool first = true;
		stack<T> tmp;
		TreePrintVisitor<T> visitor(cout);
		if (first)
			first = false;
		else 
			cout << ", ";

		cout << "{";
		while (!result.empty())
		{
			tmp.push(result.top());
			visitor.Visit(result.top());
			result.pop();
		}
		cout << "}";

		while (!tmp.empty())
		{
			result.push(tmp.top());
			tmp.pop();
		}
	}
};

void FundAllPaths(BinaryTree<int>* root, int count)
{
	CountVisitor<int> visitor(count);
	
	if (root->IsEmpty())
		return;

	root->DepthFirstTraversal(visitor);

	if (visitor.IsDone())
		return;
}

/* 编写一个程序，把一个有序整数数组放到二叉树中, 要求越平衡越好.
    算法思想:  广度优先遍历.
    Example:
    const size_t N = 6;
    int array[6] = {1, 2, 3, 4, 5, 6};
    BinaryTree<int>* BuildBinaryTree(array, N)
 */
BinaryTree<int>* BuildBinaryTree(int array[], size_t length)
{
    queue<BinaryTree<int>*> treeQueue;
    
    size_t i;
    BinaryTree<int>* root = new BinaryTree<int>(array[0]);
    treeQueue.push(root);
    for (i = 1; i < length; ++i)
    {
        BinaryTree<int>* tree = treeQueue.front();
        treeQueue.pop();

        BinaryTree<int>* left = new BinaryTree<int>(array[i]);
        tree->AttachLeft(left);
        treeQueue.push(left);

        if (++i >= length)
        {
            break;
        }

        BinaryTree<int>* right = new BinaryTree<int>(array[i]);
        tree->AttachRight(right);
        treeQueue.push(right);
    }

    return root;
}

/* 判断整数序列是不是二叉搜索树的后序遍历结果。
    算法思想：在后序遍历得到的序列中，最后一个元素为树的根结点。从头开始扫描这个序列，比根结点小的
    元素都应该位于序列的左半部分；从第一个大于跟结点开始到跟结点前面的一个元素为止，所有元素都应该
    大于跟结点，因为这部分元素对应的是树的右子树。根据这样的划分，把序列划分为左右两部分，我们递归
    地确认序列的左、右两部分是不是都是二元查找树。
    由于不能使用动态数组，所以我们每次递归都使用同一个数组arr，通过start和length来模拟“部分”数组。
 */
bool VerifyArrayOfBST(int array[], size_t length)
{
    size_t i;
    if (length <= 1)
        return true;

    int top = array[length -1];
    for (i = 0; i < length - 1; ++i)
    {
        if (array[i] > top)
            break;
    }
	size_t leftElements = i;

    for (i = leftElements; i < length - 1; ++i)
    {
        if (array[i] < top)
            return false;
    }

    if (i > 1)
    {
        if (!VerifyArrayOfBST(array, i))
            return false;
    }
    
    if (leftElements < length - 1)
    {
        if (!VerifyArrayOfBST(array + leftElements, length - 1 - leftElements))
            return false;
    }

    return true;
}

/* 求二叉树的镜像 */
void BuildMirrorBinaryTree(BinaryTree<int>* root)
{
    if (root->IsEmpty())
        return;

    BinaryTree<int>* tmp;
    tmp = &root->Left();
    root->DetachLeft();
    root->AttachLeft(&root->Right());
    root->DetachRight();
    root->AttachRight(tmp);

    BuildMirrorBinaryTree(&root->Left());
    BuildMirrorBinaryTree(&root->Right());
}

/* 一棵排序二叉树（即二叉搜索树BST），令 f=(最大值+最小值)/2，设计一个算法，
   找出距离f值最近、大于f值的结点。复杂度如果是O(n2)则不得分。
   
 */
AVLTree<int>* FindNode(AVLTree<int>* root, int value)
{
    if (root->IsEmpty())
        return root;

    if (value > root->Key())
    {
        return FindNode(&root->Right(), value);        
    }
    else if (value == root->Key())
    {
        return &root->Right();  
    }
    else
    {
        AVLTree<int>* result = FindNode(&root->Left(), value);

        return result->IsEmpty() ? root : result;
    }
}

/* 把二叉搜索树转变成排序的双向链表 */
void BuildLinklistFromAvl(AVLTree<int>* tree)
{
}

/* 判断一颗树是否为完全二叉树 
   说明： 百度百科和书上对“完全二叉树”的定义不一样，  其他各大网站介绍“完全二叉树”判断的算法时， 
          都是按照百度百科的定义来判断的， 所以以下算法也采用百度百科的定义。
 */
bool IsFullTree(BinaryTree<int>* tree)
{
    queue<BinaryTree<int>*> treeQueue;

    treeQueue.push(tree);
    while (!treeQueue.empty())
    {
        BinaryTree<int>* top = treeQueue.front();
        treeQueue.pop();

        if (top->Left().IsEmpty())
        {       
            if (top->Right().IsEmpty())
                break;
            else
                return false;
        }
        else
        { 
            if (top->Right().IsEmpty())
            {
                treeQueue.push(&top->Left());
                break;
            }
            else
            {
                treeQueue.push(&top->Left());
                treeQueue.push(&top->Right());            
            }
        }        
    }

    while (!treeQueue.empty())
    {
        BinaryTree<int>* top = treeQueue.front();
        treeQueue.pop();

        if (!top->Right().IsEmpty() || !top->Left().IsEmpty())
        {
            return false;
        }
    }

    return true;
}

//计算排列算法
//1, 采用链式存储的栈, 递归。
/* Example:
char allElements[] = "abcdefghijklmnopqrstuvwxyz";
vector<char> elements(allElements, allElements + 5);  //总共5个元素
list<char> select;
size_t caseNum ;
caseNum = CalCombination(elements, 3, select, 0);

cout << endl << "All case is: " << caseNum << endl;
*/
size_t CalCombination(vector<char>& elements, size_t keyNum, list<char>& select, size_t caseNum)
{
    assert(elements.size() + select.size() >= keyNum);

    if (select.size() == keyNum)
    {   
        //copy(select.begin(), select.end(), ostream_iterator<char>(cout, " "));        
        cout << endl;
        return caseNum + 1;
    }

    for (auto i = elements.begin(); i != elements.end(); ++i)
    {
        if (find(select.begin(), select.end(), *i) != select.end())
            continue;

        select.push_back(*i);
        caseNum = CalCombination(elements, keyNum, select, caseNum);

        select.pop_back();
    }

    return caseNum;
}

