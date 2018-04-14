
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

/* ������ת */
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

/* �ҳ�������ĵ�����4��Ԫ�� */
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

/* �ҳ���������м�Ԫ�� */
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

/* һ���������ܳ�������һ����������ǽ�֪��һ��ָ��ĳ�ڵ��ָ��curr������������ɾ������ڵ㡣*/
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
        /* node Ϊ��������һ���ڵ�, ��ʱ����ֻ�ܱ������������ҳ������ڶ����ڵ�.... */
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

/* �жϵ������Ƿ��л�������ҵ����ġ���ʼ���㣿���֪�����ĳ��ȣ� */
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

/* ���������� 
   �㷨˼�룺 ������������ȣ� ���������������ǲ���ͨ�������±���ʵ�ǰ�ڵ��ǰһ���ڵ㡣
   �������ǿ��Զ�����������㷨��һЩ�Ķ������������ 

   ��������ʹ��ð���㷨�� ð���㷨����ѭ���Ǵ��ҵ��� ���ڼ����ڲ�ѭ���ı߽磬 �����ڲ���
   �����ռ������£� �����������ʺ�ʹ��ð���㷨��

   ����������ʹ�ò���������㷨��
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

/* �ݹ鷴תһ��ջ��Ҫ�󲻵���������һ��ͬ����ջ 
   �㷨˼��: ÿһ�εݹ鶼��¼��ǰ��top, ��interimTop ֵ, �������ѹ���ջ��. �е�������
             ð���㷨, ÿ�ζ�����ǰ��top ��ջ��.
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

/*  �����һ������ʵ������ջ 
    �㷨˼��:  ��һ��ջA��������������, �ڶ���ջ��������������
 */
class NewStack
{
public:
    void pushA(int value);
    void pushB(int value);
};

/* ���һ���㷨���ҳ������������������ڵ�������ͬ����㣬���Ӷ������O(n2)�򲻵÷֡�
   �㷨1����һ�������������ڱ���������Ѱ�ҽڵ��ͬʱ���ѴӸ����ڵ��·���ӽ�ȥ�������ڵ������
          ���������� ���ڸ��ڵ����һ�����ӽ�ȥ�������ǽ���������Ҫ��һ�����ܷ��ʵ������������
          �����������������һ��ջ�� ʱ�临�Ӷ�O(N)���ռ临�Ӷ�O(N)��

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

/* ��β��õݹ�ʵ�ֶ�������ǰ��/����/��������� 
   �㷨˼�룺�����㷨��˼�붼����root��Left��Left��Leftȫ����ջ�����Ե�һ��whileѭ�����߼���������ͬ�ġ�
   ������ϸ������2��whileѭ��������һ����ջ������ֻҪջ��Ϊ�գ���ʼ��Ҫ����ջ��Ԫ�أ���������֮ǰ��ջ��
   ����Left�ڵ㣬����ÿ���ڳ�ջ��ʱ�����Ƕ�Ҫ����Right�ڵ��Ƿ���ڡ���Ϊǰ��/����/�������˳��Ĳ�ͬ��
   �����ھ����ʵ��������Ϊ����

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
    BinaryTree<int> *previous = NULL;    //previous��ʾ���һ�η��ʹ��Ľ��

    treeStack.push(top);
    while (top != NULL || !treeStack.empty())
    {
        //�������ӷ����ߵ������� ��
        while (top != NULL && !top->Left().IsEmpty())
        {
            top = &top->Left();
            treeStack.push(top);
        }
        
        top = treeStack.top();    
        if (top->Right().IsEmpty() || &top->Right() == previous)
        {
            //û���Һ��ӣ� �������Һ��Ӹոձ����ʹ�
            treeStack.pop();
            visitor.Visit(top->Key());
            previous = top;
            top = NULL;
        }
        else
        {
			//���Һ���, �����Һ���.
            top = &top->Right();
            treeStack.push(top);
        }
    }
}

/* �ڶ��������ҳ���Ϊĳһֵ������·�� 
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

/* ��дһ�����򣬰�һ��������������ŵ���������, Ҫ��Խƽ��Խ��.
    �㷨˼��:  ������ȱ���.
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

/* �ж����������ǲ��Ƕ����������ĺ�����������
    �㷨˼�룺�ں�������õ��������У����һ��Ԫ��Ϊ���ĸ���㡣��ͷ��ʼɨ��������У��ȸ����С��
    Ԫ�ض�Ӧ��λ�����е���벿�֣��ӵ�һ�����ڸ���㿪ʼ�������ǰ���һ��Ԫ��Ϊֹ������Ԫ�ض�Ӧ��
    ���ڸ���㣬��Ϊ�ⲿ��Ԫ�ض�Ӧ�������������������������Ļ��֣������л���Ϊ���������֣����ǵݹ�
    ��ȷ�����е������������ǲ��Ƕ��Ƕ�Ԫ��������
    ���ڲ���ʹ�ö�̬���飬��������ÿ�εݹ鶼ʹ��ͬһ������arr��ͨ��start��length��ģ�⡰���֡����顣
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

/* ��������ľ��� */
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

/* һ�������������������������BST������ f=(���ֵ+��Сֵ)/2�����һ���㷨��
   �ҳ�����fֵ���������fֵ�Ľ�㡣���Ӷ������O(n2)�򲻵÷֡�
   
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

/* �Ѷ���������ת��������˫������ */
void BuildLinklistFromAvl(AVLTree<int>* tree)
{
}

/* �ж�һ�����Ƿ�Ϊ��ȫ������ 
   ˵���� �ٶȰٿƺ����϶ԡ���ȫ���������Ķ��岻һ����  ����������վ���ܡ���ȫ���������жϵ��㷨ʱ�� 
          ���ǰ��հٶȰٿƵĶ������жϵģ� ���������㷨Ҳ���ðٶȰٿƵĶ��塣
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

//���������㷨
//1, ������ʽ�洢��ջ, �ݹ顣
/* Example:
char allElements[] = "abcdefghijklmnopqrstuvwxyz";
vector<char> elements(allElements, allElements + 5);  //�ܹ�5��Ԫ��
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

