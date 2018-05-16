#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#define TEST_HEADER printf("\n==========================%s=====================\n",__FUNCTION__)

SearchTreeNode* CreateNode(SearchTreeType value)
{
    SearchTreeNode* new_node=(SearchTreeNode* )malloc(sizeof(SearchTreeNode));
    new_node->key=value;
    new_node->lchild=NULL;
    new_node->rchild=NULL;

    return new_node;
}
void SearchTreeInit(SearchTreeNode** root)
{
    if(root==NULL)
    {
        return;
    }
    *root=NULL;
}

void SearchTreeInsertByLoop(SearchTreeNode** root, SearchTreeType key)
{
    if(root==NULL)
    {
        return;
    }
    if(*root==NULL)
    {
        SearchTreeNode* new_node=CreateNode(key);
        *root=new_node;
    }
    else
    {
        //先找到要插入的位置 
        //cur表示要插入的位置
        //pre表示要插入的位置的父结点
        SearchTreeNode* cur=*root;
        SearchTreeNode* pre=NULL;
        while(cur)
        {
            if(cur->key>key)
            {
                pre=cur;
                cur=cur->lchild;
            }
            else if(cur->key<key)
            {
                pre=cur;
                cur=cur->rchild;
            }
            else
            {
                break;
            }
        }
        //此时已经可以插入了
        if(pre->key>key)
        {
            pre->lchild=CreateNode(key);
        }
        else
        {
            pre->rchild=CreateNode(key);
        }
    }
}

SearchTreeNode* SearchTreeFindByLoop(SearchTreeNode* root, SearchTreeType to_find)
{
    if(root==NULL)
    {
        return NULL;
    }
    SearchTreeNode* cur=root;
    while(cur!=NULL)
    {
        if(cur->key>to_find)
        {
            cur=cur->lchild;
        }
        else if(cur->key<to_find)
        {
            cur=cur->rchild;
        }
        else
        {
            break;
        }
    }
    return cur;
}
void SearchTreeRemoveByLoop(SearchTreeNode** root, SearchTreeType key)
{
    if(root==NULL)
    {
        return;
    }
    if(*root==NULL)
    {
        return;
    }
    SearchTreeNode* to_remove=*root;
    SearchTreeNode* parent=NULL;
    //先找到删除的位置
    while(to_remove!=NULL)
    {
        if(to_remove->key>key)
        {
            parent=to_remove;
            to_remove=to_remove->lchild;
        }
        else if(to_remove->key<key)
        {
            parent=to_remove;
            to_remove=to_remove->rchild;
        }
        else
        {
            break;
        }
    }
    //找不到的情况
    if(to_remove==NULL)
    {
        return;
    }
    //此时已经找到位置
    //分情况讨论
    //1.无左右子树
    if(to_remove->lchild==NULL&&to_remove->rchild==NULL)
    {
        if(parent->key>key)
        {
            parent->lchild=NULL;
            free(to_remove);
        }
        else
        {
            parent->rchild=NULL;
            free(to_remove);
        }
    }

    //2.只有左子树
    else if(to_remove->lchild!=NULL&&to_remove->rchild==NULL)
    {
        parent->lchild=to_remove->lchild;
        free(to_remove);
    }
    //3.只有右子树
    else if(to_remove->lchild==NULL&&to_remove->rchild != NULL)
    {
        parent->rchild=to_remove->rchild;
        free(to_remove);
    }
    
    //4.有左右子树
    else
    {
        SearchTreeNode* min=to_remove->rchild;
        while(min->lchild!=NULL)
        {
            parent=min;
            min=min->lchild;
        }
        //此时找到了最小的结点
        to_remove->key=min->key;
        parent->lchild=min->rchild;
        free(min);
    }
}
////////////////////////////////////////////
//以下是递归版本
/////////////////////////////////////////////
void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key)
{
    if(root==NULL)
    {
        return;
    }
    //空树的情况
    if(*root==NULL)
    {
        SearchTreeNode* new_node=CreateNode(key);
        *root=new_node;
        return;
    }
    SearchTreeNode* to_find=*root;
    if(key>to_find->key)
    {
        SearchTreeInsert(&to_find->rchild,key);
    }
    else if(key<to_find->key)
    {
        SearchTreeInsert(&to_find->lchild,key);
    }
    else
    {
        return;//默认不允许出现相同元素
    }
}

SearchTreeNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(to_find>root->key)
    {
        return SearchTreeFind(root->rchild,to_find);
    }
    else if(to_find<root->key)
    {
        return SearchTreeFind(root->lchild,to_find);
    } 
    else
    {
        return root;
    }
}
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key)
{
    if(root==NULL)
    {
        return;
    }
    if(*root==NULL)
    {
        return;
    }
    SearchTreeNode* cur=*root;
    if(key>cur->key)
    {
        return SearchTreeRemove(&cur->rchild,key);
    }
    else if(key<cur->key)
    {
        return SearchTreeRemove(&cur->lchild,key);
    } 
    else
    {
        //找得到删除的位置
        //1.无左右子树
        if(cur->lchild==NULL&&cur->rchild==NULL)
        {
            *root=NULL;
            free(cur);
            return;
        }
        //2.有左子树
        else if(cur->lchild!=NULL&&cur->rchild==NULL)
        {
            *root=cur->lchild;
            free(cur);
            return;
        }
        //3.有右子树
        else if(cur->lchild==NULL&&cur->rchild!=NULL)
        {
            *root=cur->rchild;
            free(cur);
            return;
        }
        //4.既有左子树又有右子树
        else if(cur->lchild!=NULL&&cur->rchild!=NULL)
        {
            SearchTreeNode* min=cur->rchild;
            while(min->lchild!=NULL)
            {
                min=min->lchild;
            }
            cur->key=min->key;
            SearchTreeRemove(&cur->rchild,min->key);
            return;
        }
    }
    return;
}
/////////////////////////////////////////////
//测试代码
/////////////////////////////////////////////
void TestInit()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
}
void PreOrder(SearchTreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    printf("%c ",root->key);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}
void InOrder(SearchTreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    InOrder(root->lchild);
    printf("%c ",root->key);
    InOrder(root->rchild);
}
void SearchTreePrintChar(SearchTreeNode* root,const char* msg)
{
    printf("%s\n",msg);
    printf("先序遍历结果是：");
    PreOrder(root);
    printf("\n");
    printf("中序遍历结果是：");
    InOrder(root);
    printf("\n");
}

void TestInsert()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'x');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreePrintChar(root,"插入五个元素");
    
}
void TestInsertByLoop()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsertByLoop(&root,'f');
    SearchTreeInsertByLoop(&root,'b');
    SearchTreeInsertByLoop(&root,'x');
    SearchTreeInsertByLoop(&root,'d');
    SearchTreeInsertByLoop(&root,'a');
    SearchTreePrintChar(root,"插入五个元素");
    
}
void TestFind()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'x');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreePrintChar(root,"插入五个元素");
    SearchTreeNode* to_find=SearchTreeFind(root,'b');
    printf("d expect %p,actual %p\n", root->lchild ,to_find);
}
void TestFindByLoop()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'x');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreePrintChar(root,"插入五个元素");
    SearchTreeNode* to_find=SearchTreeFindByLoop(root,'b');
    printf("d expect %p,actual %p\n", root->lchild ,to_find);
}
void TestRemove()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'x');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'g');
    SearchTreePrintChar(root,"插入8个元素");
    SearchTreeRemove(&root,'a');
    SearchTreePrintChar(root,"删除一个无左右子树的元素");
    SearchTreeRemove(&root,'b');
    SearchTreePrintChar(root,"删除一个有左右子树的元素");
    SearchTreeRemove(&root,'z');
    SearchTreePrintChar(root,"删除一个不存在的元素");

}
void TestRemoveByLoop()
{
    TEST_HEADER;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'x');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'g');
    SearchTreePrintChar(root,"插入8个元素");
    SearchTreeRemoveByLoop(&root,'a');
    SearchTreePrintChar(root,"删除一个无左右子树的元素");
    SearchTreeRemoveByLoop(&root,'b');
    SearchTreePrintChar(root,"删除一个有左右子树的元素");
    SearchTreeRemoveByLoop(&root,'z');
    SearchTreePrintChar(root,"删除一个不存在的元素");

}
int main()
{
    TestInit();
    TestInsert();
    TestInsertByLoop();
    TestFind();
    TestFindByLoop();
    TestRemove();
    TestRemoveByLoop();
    return 0;
}
