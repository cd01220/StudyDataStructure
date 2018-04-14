#include ".\BTree.h"
#include <limits.h>

BTree::BTree (unsigned int degree): MWayTree(degree),parent(0)
{
	return;
}

//参数说明：.
BTree::BTree (unsigned int degree, BTree& prt): MWayTree(degree)
{
	parent = &prt;
	return;
}

///////////////////////////////////////////////////////////////////////////////
//说明：本函数是学习时自己添加的代码， 添加的依据见原书269页的相关说明。
//功能：
//参数: prt 当前树的父。
//返回值 : 无。
//使用方法： 参见InsertPair()。
//最后修改日期： 2005-12-5。
///////////////////////////////////////////////////////////////////////////////
void BTree::AttachLeftHalfOf (BTree const& prt)
{
	//函数在看了书的的大意后，自己写的， 结果在调整个类的过程中，因为本函数的问题，
	//用了三天时间才使TestBTree（）能够正常运行。  共修改的本函数的错误超过8处。 在写一
	//新函数前，一定要多思考， 写后也要做单独的测试。  否则到联调时才发现问题，非常
	//影响进度。
    subtree[0] = prt.subtree[0];
    dynamic_cast<BTree *>(subtree[0])->parent = this;
    for(unsigned int i = 1; i <= (m+1)/2 - 1; ++i)
	{
		key[i] = prt.key[i];
		subtree[i] = prt.subtree[i];
		dynamic_cast<BTree *>(subtree[i])->parent = this;
		numberOfKeys++;
	}

}

///////////////////////////////////////////////////////////////////////////////
//说明：本函数是学习时自己添加的代码， 添加的依据见原书269页的相关说明。
//功能：
//参数: prt 当前树的父。。
//返回值 : 无。
//使用方法： 参见InsertPair()。
//最后修改日期： 2005-12-5。
///////////////////////////////////////////////////////////////////////////////
void BTree::AttachRightHalfOf (BTree const& prt, 
                               Object& extraKey, 
                               BTree& extraTree)
{
	subtree[0] = prt.subtree[(m+1)/2];
	dynamic_cast<BTree *>(subtree[0])->parent = this;
    unsigned int firstKey = (m+1)/2 + 1;
	for(unsigned int i = firstKey; i <= m - 1; ++i)
	{
		key[i - firstKey + 1] = prt.key[i];
		subtree[i - firstKey + 1] = prt.subtree[i];
		dynamic_cast<BTree *>(subtree[i - firstKey + 1])->parent = this;
		numberOfKeys++;
	}
    numberOfKeys++;
    key[numberOfKeys] = &extraKey;
    subtree[numberOfKeys] = &extraTree;
    dynamic_cast<BTree *>(subtree[numberOfKeys])->parent = this;
	return;
}

///////////////////////////////////////////////////////////////////////////////
//说明：本函数是学习时自己添加的代码， 添加的依据见原书269页的相关说明。
//参数:index 关键字插入的位置。object 需要插入的关键字。
//返回值 : 插入后，关键字数组的最右边端的关键字。
//最后修改日期： 2005-12-05。
///////////////////////////////////////////////////////////////////////////////
Object& BTree::InsertKey (unsigned int index, Object& object)
{
    Object& objRet = (index == numberOfKeys+1 ? object : *key[numberOfKeys]);

    unsigned int loop = std::min(numberOfKeys+1, m - 1);
	while(loop-- > index)
	{
		key[loop + 1] = key[loop];
	}
    if(index < m)
    {
	    key[index] = &object;
    }
	return objRet;    
}

///////////////////////////////////////////////////////////////////////////////
//说明：本函数是学习时自己添加的代码， 添加的依据见原书269页的相关说明。
//参数:index 关键字插入的位置。tree 需要插入的子树。
//返回值 : 插入后，子树数组的最右边端的子树。
//最后修改日期： 2005-12-05
///////////////////////////////////////////////////////////////////////////////
BTree& BTree::InsertSubtree (unsigned int index, BTree& tree)
{ 
    BTree& treeRet = (index == numberOfKeys+1 ? tree : (BTree&)*subtree[numberOfKeys]);

    unsigned int loop = std::min(numberOfKeys+1, m-1);
	while(loop-- > index)
    {
        subtree[loop+1] = subtree[loop];
    }
    if(index < m)
    {
	    subtree[index] = &tree;
    }

    return treeRet;
}

//added by liuhao
void BTree::AttachSubtree (unsigned int index, MWayTree& tree)
{	
	subtree[index] = &tree;
	return;
}

//added by liuhao.
void BTree::AttachKey (unsigned int index, Object& object)
{
	key [index] = &object;
	return;
}

void BTree::Insert (Object& object)
{
    if (IsEmpty ())
    {
	    if (parent == 0)
	    {
	        AttachSubtree (0, *new BTree (m, *this));
	        AttachKey (1, object);
	        AttachSubtree (1, *new BTree (m, *this));
	        numberOfKeys = 1;
	    }
	    else
	        parent->InsertPair (object, *new BTree (m, *parent));
    }
    else
    {
	    unsigned int const index = FindIndex (object);
	    if (index != 0 && object == *key [index])
	        throw invalid_argument ("duplicate key");
	    subtree [index]->Insert (object);
    }
}

void BTree::InsertPair (Object& object, BTree& child)
{
    unsigned int const index = FindIndex (object);
    BTree& extraTree = InsertSubtree (index + 1, child);
    Object& extraKey = InsertKey (index + 1, object);

    if (++numberOfKeys == m)
    {
	    if (parent == 0)
	    {
	        BTree& left = *new BTree (m, *this);
	        BTree& right = *new BTree (m, *this);
	        left.AttachLeftHalfOf (*this);
	        right.AttachRightHalfOf (*this, extraKey, extraTree);
	        AttachSubtree (0, left);
            //中点或中点左边的位置为(m+1)/2，计算方式应该在其它地方也可以用到。
	        AttachKey (1, *key [(m + 1)/2]);  
	        AttachSubtree (1, right);
	        numberOfKeys = 1;
	    }
	    else
	    {
            //如果溢出节点不是根节点， 具体说明见269页，倒数第二段。
	        numberOfKeys = (m + 1)/2 - 1;
	        BTree& right = *new BTree (m, *parent);
	        right.AttachRightHalfOf (*this, extraKey, extraTree);
	        parent->InsertPair (*key [(m + 1)/2], right);
	    }
    }
}

//added by liuhao 2005-12-05, 根据270页描述的方法，分4种情况处理。
void BTree::Withdraw (Object& object)
{
    if (IsEmpty ())
	    throw invalid_argument ("object not found");
    unsigned int index = FindIndex (object);
    if (index != 0 && object == *key [index])
    {
	    if (!subtree [index - 1U]->IsEmpty ())
	    {
	        Object& max = subtree [index - 1U]->FindMax ();
	        key [index] = &max;
	        subtree [index - 1U]->Withdraw (max);
	    }
	    else if (!subtree [index]->IsEmpty ())
	    {
	        Object& min = subtree [index]->FindMin ();
	        key [index] = &min;
	        subtree [index]->Withdraw (min);
	    }
	    else
	    {
            if(numberOfKeys <= m / 2 - 1)
            {
                Balance ();  //删除数据项后关键字数等于m/2-2，需要做平衡操作。
                index = FindIndex (object);
            }           
        
	        --numberOfKeys;
	        delete subtree [index];
	        for(unsigned int i = index; i <= numberOfKeys; ++i)
	        {
		        key [i] = key [i + 1];
		        subtree [i] = subtree [i + 1];
	        }
	        //if (numberOfKeys == 0)
		       // delete subtree [0];  
	    }
    }
    else
	    subtree [index]->Withdraw (object);

    //如果删除操作使根节点成为了空节点， 且第0棵子树不为空,
    //把第0棵子树的内容移到根节点。added by liuhao 2005-12-09
    if(numberOfKeys == 0 
        && parent == 0 
        && Subtree(0).numberOfKeys != 0)
    {
        BTree& tree = Subtree(0);
        tree.Subtree(0).parent = this;
        subtree [0] = &tree.Subtree(0);
        for(unsigned int i = 1; i <= tree.numberOfKeys; ++i)
        {
            tree.Subtree(i).parent = this;
            subtree [i] = tree.subtree[i];
            key[i] = tree.key[i];
        }
        
        numberOfKeys = tree.numberOfKeys;
        tree.numberOfKeys = 0;
        delete &tree;
    }
}

BTree& BTree::Subtree (unsigned int i) const
{
    return dynamic_cast<BTree&>(*subtree[i]);
}

//合并两个节点。  added by liuhao 2005-12-07 参考原书270页。
void BTree::Unite(unsigned int left, unsigned int right, unsigned int invoker)
{
    Balance (); 
    BTree& lTree = Subtree(left);
    BTree& rTree = Subtree(right);

    unsigned int i = 0;
    if(invoker == 0)
    {
        //把当前数据项和右子树的内容添加到左子树。 
        lTree.InsertKey(++lTree.numberOfKeys, *key[right]);
        lTree.InsertSubtree(lTree.numberOfKeys, rTree.Subtree(0));
        for(i = 1; i <= rTree.numberOfKeys; ++i)
        {
            lTree.InsertKey(++lTree.numberOfKeys, *rTree.key[i]);
            lTree.InsertSubtree(lTree.numberOfKeys, rTree.Subtree(i));
        }
        rTree.numberOfKeys = 0;
        delete &rTree;
        subtree[left] = &lTree;
    }
    else
    {
        //把当前数据项和左子树的内容添加到右子树。 
        rTree.numberOfKeys += 1 + lTree.numberOfKeys;
        rTree.InsertSubtree(0, lTree.Subtree(0));        
        for(i = 1; i <= lTree.numberOfKeys; ++i)
        {
            rTree.InsertKey(i, *lTree.key[i]);
            rTree.InsertSubtree(i, lTree.Subtree(i));
        }
        rTree.InsertKey(i, *key[right]);        

        lTree.numberOfKeys = 0;
        delete &lTree;
        subtree[left] = &rTree;
    }
    
    
    //当前数据项右边的关键字和子树左移一位， 并且当前关键字数减1。
    for(i = right; i <= numberOfKeys - 1; ++i)
    {
        key[i] = key[i + 1];
        subtree[i] = subtree[i + 1];
    }
    --numberOfKeys;
}

void BTree::LLRotation (unsigned int left, unsigned int right)
{
    BTree& lTree = dynamic_cast<BTree &>(*subtree[left]);
    BTree& rTree = dynamic_cast<BTree &>(*subtree[right]);
    rTree.InsertKey(0, *key[right]);
    rTree.InsertSubtree(0, dynamic_cast<BTree &>(*lTree.subtree[lTree.numberOfKeys]));
    key[right] = lTree.key[lTree.numberOfKeys];
    --lTree.numberOfKeys;  
    ++rTree.numberOfKeys;
}

void BTree::RRRotation (unsigned int left, unsigned int right)
{
    BTree& lTree = Subtree(left);
    BTree& rTree = Subtree(right);
    lTree.InsertKey(++lTree.numberOfKeys, *key[right]);
    lTree.InsertSubtree(lTree.numberOfKeys, rTree.Subtree(0));
    key[right] = rTree.key[1];
    rTree.subtree[0] = rTree.subtree[1];
    for(unsigned int i = 1; i <= rTree.numberOfKeys - 1; ++i) 
    {
        rTree.key[i] = rTree.key[i+1];
        rTree.subtree[i] = rTree.subtree[i + 1];
    }
    --rTree.numberOfKeys;
}

void BTree::Balance ()
{
    if(0 == parent || m <= 3 || numberOfKeys > m / 2 - 1)
    {
        //当前节点为根节点，不需要平衡操作。
        //原书270页介绍的算法不能处理m <=2 的情况。
        return;
    }
    unsigned int index = UINT_MAX;

    for(unsigned int i = 0; i <= parent->numberOfKeys; ++i)
    {
        if(this == &parent->Subtree(i))
        {
            index = i;
            break;
        }
    }
    if(index == UINT_MAX)
    {
        throw out_of_range ("parent 中找不到当前子树!");
    }

    if(index != 0 && parent->Subtree(index - 1).numberOfKeys >= m / 2)
    {
        //LL旋转。
        parent->LLRotation(index - 1, index);
        
    }
    else if(index != numberOfKeys 
            && parent->Subtree(index + 1).numberOfKeys >= m / 2)
    {
        //RR旋转。
        parent->RRRotation(index, index + 1);
    }
    else
    {
        //合并子树
        if(index == 0)
        {
            parent->Unite(index, index + 1, 0);
        }
        else
        {
            parent->Unite(index - 1, index, 1);
        } 
    }

}
