#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct treeNode
{
    long item;
    int count;
    struct treeNode *pLeft;
    struct treeNode *pRight;
};


struct treeNode *createNode(long value);
struct treeNode *addNode(long value, struct treeNode *pNode);
void listNodes(struct treeNode *pNode);     //遍历，升序遍历
void freeNodes(struct treeNode *pNode);     //释放内存


int main(void)
{
    long newValue = 0;
    struct treeNode *pRoot = NULL;
    char answer = 'n';

    do
    {
        printf("Enter the node value:");
        scanf("%ld", &newValue);

        if(NULL == pRoot)
        {
            pRoot = createNode(newValue);
        }
        else
        {
            addNode(newValue, pRoot);
        }

        printf("Do you want to enter another(Y or n)?:");
        scanf(" %c", &answer);  //注意，%c前面一定要加个空格，因为%c会读取上次输入的回车等字符来填充

    }while(tolower(answer) == 'y');
    
    printf("升序遍历：");
    listNodes(pRoot);
    printf("\n");
    freeNodes(pRoot);

    return 0;
}



struct treeNode *createNode(long value)
{
    struct treeNode *pNode = (struct treeNode *)malloc(sizeof(struct treeNode));

    if(NULL == pNode)
    {
        printf("创建节点不成功，分配内存失败！\n");
        exit(1);
    }
    
    pNode->item = value;
    pNode->count = 1;
    pNode->pLeft = pNode->pRight = NULL;
    return pNode;
}


struct treeNode *addNode(long value, struct treeNode *pNode)
{
    if(NULL == pNode) //没有根节点，则创建并返回
    {
        return createNode(value);
    }

    if(value == pNode->item)
    {
        pNode->count++;
        return pNode;
    }

    if(value < pNode->item)
    {
        if(NULL == pNode->pLeft)
        {
            pNode->pLeft = createNode(value);
            return pNode->pLeft;
        }
        else
        {
            return addNode(value, pNode->pLeft);
        }
    }
    else
    {
        if(NULL == pNode->pRight)
        {
            pNode->pRight = createNode(value);
            return pNode->pRight;
        }
        else
        {
            return addNode(value, pNode->pRight);
        }
    }
}


void listNodes(struct treeNode *pNode)  //遍历，升序遍历
{
    int i = 0;

    if(pNode->pLeft != NULL)
    {
        listNodes(pNode->pLeft);
    }

    for(i = 0; i < pNode->count; i++)
    {
        printf("%ld ", pNode->item);
    }

    if(pNode->pRight != NULL)
    {
        listNodes(pNode->pRight);
    }
}


void freeNodes(struct treeNode *pNode)
{
    if(NULL == pNode)
    {
        return ;
    }

    if(pNode->pLeft != NULL)
    {
        freeNodes(pNode->pLeft);
    }

    if(pNode->pRight != NULL)
    {
        freeNodes(pNode->pRight);
    }

    free(pNode);
}



