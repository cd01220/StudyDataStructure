#include ".\BTree.h"
#include <limits.h>

BTree::BTree (unsigned int degree): MWayTree(degree),parent(0)
{
	return;
}

//����˵����.
BTree::BTree (unsigned int degree, BTree& prt): MWayTree(degree)
{
	parent = &prt;
	return;
}

///////////////////////////////////////////////////////////////////////////////
//˵������������ѧϰʱ�Լ���ӵĴ��룬 ��ӵ����ݼ�ԭ��269ҳ�����˵����
//���ܣ�
//����: prt ��ǰ���ĸ���
//����ֵ : �ޡ�
//ʹ�÷����� �μ�InsertPair()��
//����޸����ڣ� 2005-12-5��
///////////////////////////////////////////////////////////////////////////////
void BTree::AttachLeftHalfOf (BTree const& prt)
{
	//�����ڿ�����ĵĴ�����Լ�д�ģ� ����ڵ�������Ĺ����У���Ϊ�����������⣬
	//��������ʱ���ʹTestBTree�����ܹ��������С�  ���޸ĵı������Ĵ��󳬹�8���� ��дһ
	//�º���ǰ��һ��Ҫ��˼���� д��ҲҪ�������Ĳ��ԡ�  ��������ʱ�ŷ������⣬�ǳ�
	//Ӱ����ȡ�
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
//˵������������ѧϰʱ�Լ���ӵĴ��룬 ��ӵ����ݼ�ԭ��269ҳ�����˵����
//���ܣ�
//����: prt ��ǰ���ĸ�����
//����ֵ : �ޡ�
//ʹ�÷����� �μ�InsertPair()��
//����޸����ڣ� 2005-12-5��
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
//˵������������ѧϰʱ�Լ���ӵĴ��룬 ��ӵ����ݼ�ԭ��269ҳ�����˵����
//����:index �ؼ��ֲ����λ�á�object ��Ҫ����Ĺؼ��֡�
//����ֵ : ����󣬹ؼ�����������ұ߶˵Ĺؼ��֡�
//����޸����ڣ� 2005-12-05��
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
//˵������������ѧϰʱ�Լ���ӵĴ��룬 ��ӵ����ݼ�ԭ��269ҳ�����˵����
//����:index �ؼ��ֲ����λ�á�tree ��Ҫ�����������
//����ֵ : �����������������ұ߶˵�������
//����޸����ڣ� 2005-12-05
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
            //�е���е���ߵ�λ��Ϊ(m+1)/2�����㷽ʽӦ���������ط�Ҳ�����õ���
	        AttachKey (1, *key [(m + 1)/2]);  
	        AttachSubtree (1, right);
	        numberOfKeys = 1;
	    }
	    else
	    {
            //�������ڵ㲻�Ǹ��ڵ㣬 ����˵����269ҳ�������ڶ��Ρ�
	        numberOfKeys = (m + 1)/2 - 1;
	        BTree& right = *new BTree (m, *parent);
	        right.AttachRightHalfOf (*this, extraKey, extraTree);
	        parent->InsertPair (*key [(m + 1)/2], right);
	    }
    }
}

//added by liuhao 2005-12-05, ����270ҳ�����ķ�������4���������
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
                Balance ();  //ɾ���������ؼ���������m/2-2����Ҫ��ƽ�������
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

    //���ɾ������ʹ���ڵ��Ϊ�˿սڵ㣬 �ҵ�0��������Ϊ��,
    //�ѵ�0�������������Ƶ����ڵ㡣added by liuhao 2005-12-09
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

//�ϲ������ڵ㡣  added by liuhao 2005-12-07 �ο�ԭ��270ҳ��
void BTree::Unite(unsigned int left, unsigned int right, unsigned int invoker)
{
    Balance (); 
    BTree& lTree = Subtree(left);
    BTree& rTree = Subtree(right);

    unsigned int i = 0;
    if(invoker == 0)
    {
        //�ѵ�ǰ���������������������ӵ��������� 
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
        //�ѵ�ǰ���������������������ӵ��������� 
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
    
    
    //��ǰ�������ұߵĹؼ��ֺ���������һλ�� ���ҵ�ǰ�ؼ�������1��
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
        //��ǰ�ڵ�Ϊ���ڵ㣬����Ҫƽ�������
        //ԭ��270ҳ���ܵ��㷨���ܴ���m <=2 �������
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
        throw out_of_range ("parent ���Ҳ�����ǰ����!");
    }

    if(index != 0 && parent->Subtree(index - 1).numberOfKeys >= m / 2)
    {
        //LL��ת��
        parent->LLRotation(index - 1, index);
        
    }
    else if(index != numberOfKeys 
            && parent->Subtree(index + 1).numberOfKeys >= m / 2)
    {
        //RR��ת��
        parent->RRRotation(index, index + 1);
    }
    else
    {
        //�ϲ�����
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
