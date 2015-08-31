#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


typedef int ElemType;
typedef struct Lnode
{
    ElemType data;
    struct Lnode* next;
}Lnode,*LinkList;


LinkList InitLinkList(void);    //初始化
void LinkListInsert(LinkList, ElemType, int);   //插入
void LinkListDelete(LinkList, int i);   //删除
int LinkListLocate(LinkList, ElemType, int *); //查找
void LinkListTraverse(LinkList, void(*visit)(ElemType));    //转置
void LinkListInverse_set(LinkList);
void LinkListUnion(LinkList, LinkList, int(*compare)(ElemType, ElemType));
void Visit(ElemType);
int Compare(ElemType, ElemType);


int main()
{
    int length_a, length_b, i, j, w;
    ElemType temp, x;
    LinkList La, Lb;
    La = InitLinkList();
    Lb = InitLinkList();
    printf("请输入链表La的长度：");
    scanf("%d", &length_a);
    printf("请连续输入%d个要添加到La的数，以空格隔开：", length_a);
    for(i=1; i<=length_a; i++)
    {
        scanf("%d", &temp);
        LinkListInsert(La, temp, i);
    }
    printf("创建好的链表La=");
    LinkListTraverse(La, &Visit);
    printf("\n");
    printf("请输入插入到La中的元素x和插入的位置i：");
    scanf("%d %d", &x, &i);
    LinkListInsert(La, x, i);
    printf("插入数据过后的La=");
    LinkListTraverse(La, &Visit);
    printf("\n");
    printf("请输入La要删除元素的位置：");
    scanf("%d", &i);
    LinkListDelete(La, i);
    printf("删除一个元素后的La=");
    LinkListTraverse(La, &Visit);
    printf("\n");
    printf("输入La要查找的元素：");
    scanf("%d", &x);
    if(!LinkListLocate(La, x, &w))
        printf("没有找到\n");
    else
        printf("找到了，%d在第%d个位置\n", x, w);
    LinkListInverse_set(La);
    printf("转置后的La=");
    LinkListTraverse(La, &Visit);
    printf("\n");
    printf("******************\n");
    printf("请输入链表Lb的长度：");
    scanf("%d", &length_b);
    printf("请连续输入%d个要添加到Lb的数，以空格隔开：", length_b);
    for(j=1; j<=length_b;j++)
    {
        scanf("%d", &temp);
        LinkListInsert(Lb, temp, j);
    }
    LinkListUnion(La, Lb, &Compare);
    printf("合并La和Lb后的链表=");
    LinkListTraverse(La, &Visit);
    printf("\n");
    return 0;


} //the end of main


LinkList InitLinkList(void)
{
    LinkList p;
    p = (LinkList)malloc(sizeof(Lnode));
    p->next = NULL;
    return p;
}

void LinkListInsert(LinkList L, ElemType e, int i)
{
    if(i<=0)
    {
        printf("插入元素位置不正确\n");
        exit(0);
    }
    LinkList p = L,q = NULL;
    int j = 0;
    while(p && j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!p)
    {
        printf("插入位置不正确\n");
        exit(0);
    }
    q = (LinkList)malloc(sizeof(Lnode));
    q->data = e;
    q->next = p->next;
    p->next = q;

}


void LinkListDelete(LinkList L, int i)
{
    if(i <= 0)
    {
        printf("删除位置小于等于0\n");
        exit(0);
    }
    int j;
    LinkList p, q;
    p = L;
    for(j = 0; p->next && j<i-1;j++)
        p = p->next;
    if(!(p->next))
    {
        printf("删除的位置太大\n");
        exit(0);
    }
    q = p->next;
    p->next = p->next->next;
    free(q);

}

int LinkListLocate(LinkList L, ElemType e, int *w)
{
    int i = 1;
    LinkList p = L->next;
    while(p && p->data!=e)
    {
        p = p->next;
        i++;
    }
    if(!p)
        return 0;
    else
    {
        *w = i;
        return 1;
    }
}


void LinkListTraverse(LinkList L, void(*visit)(ElemType))
{
    LinkList p = L->next;
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}


void LinkListInverse_set(LinkList L)
{
    LinkList p, q, ptrtemp;
    p = L->next;
    q = p->next;
    p->next = NULL;
    while(q)
    {
        ptrtemp = q->next;
        q->next = p;
        p = q;
        q =ptrtemp;
    }
    L->next = p;

}


void LinkListUnion(LinkList La, LinkList Lb, int(*compare)(ElemType e1, ElemType e2))
{
    LinkList pa = La->next, pb = Lb->next, pc = La;
    while(pa && pb)
    {
        if(compare(pa->data, pb->data) <= 0)
        {
            pc->next = pa;
            pa = pa->next;
            pc = pc->next;
        }
        else
        {
            pc->next = pb;
            pb = pb->next;
            pc = pc->next;
        }
    }
    if(pa)
    {
        pc->next = pa;
    }
    else
    {
        pc->next = pb;
    }
}


void Visit(ElemType e)
{
    printf("%d ", e);
}

int Compare(ElemType e1, ElemType e2)
{
    return e1-e2;
}









