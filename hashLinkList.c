#include <stdio.h>
#include <stdlib.h>


/*哈希链表的实现，添加，删除，查找，遍历等*/

#define HASH_TABLE_LENGTH 100   //哈希表的大小

typedef int ElemType;



//链表结构
typedef struct Link_Node
{
    ElemType id;
    ElemType data;
    struct Link_Node *next;
}Link_Node,*Link_Node_Ptr;

//哈希表结构
typedef struct Hash_Head
{
    struct Link_Node *next;
}Hash_Head,*Hash_Head_Ptr;


//哈希表
Hash_Head_Ptr Hash_Table[HASH_TABLE_LENGTH];


/*函数声明*/

ElemType hash_function(ElemType id);    //哈希映射函数，输入id返回对应的位置
Link_Node_Ptr init_link_node(void); //初始化节点
Hash_Head_Ptr init_hash_head_node(void);    //初始化哈希头节点
void init_hash_table(void); //初始化哈希表Hash_Table
void add_link_node(Link_Node_Ptr newnode);  //添加节点

//查询节点，从开始遍历，返回节点的前一个指针，为了删除方便。
//root,表示如果是根节点则*root=1;否则为0；
//返回结果的前一个节点指针，如果为根节点则返回根节点，失败返回0
Link_Node_Ptr search_link_node(ElemType id, ElemType *root);

void delete_link_node(Link_Node_Ptr node);  //删除普通节点，参数节点的后一个节点，结合查找函数使用
void delete_link_root_node(Link_Node_Ptr node); //删除根节点
ElemType get_node_nums(void);   //获取所有节点的数量

//如果是根节点*root=1;否则0；成功返回普通节点前一个节点，若是根节点则返回根节点，失败0
Link_Node_Ptr get_node_of_index(ElemType index, ElemType *root);    //返回指定序号的节点

void drop_hash();   //删除hash表的所有节点
void print_hash();  //打印哈希表




int main()
{
    Link_Node_Ptr node;
    ElemType temp = 0;
    ElemType root = 0;
    ElemType i = 0;
    init_hash_table();
    printf("*****************接下来将添加5个节点*******************\n\n");
    int j = 0;
    for( ; j < 5; j++)
    {
        node = init_link_node();
        printf("正在添加第%d个节点，请输入节点id和data，中间用空格隔开：", i+1);
        scanf("%d %d", &(node->id), &(node->data));
        add_link_node(node);
    }


    printf("此刻节点数为：%d\n\n\n", get_node_nums());
    printf("删除操作，请输入你要删除的节点的id：");
    int deleteId =0;
    scanf("%d", &deleteId);


    node = search_link_node(deleteId, &temp);
    if(node != 0)
    {
        if(0 == temp)
        {
            printf("删除的是普通节点，id为：%d，数据为：%d\n", node->next->id, node->next->data);
            delete_link_node(node);
        }
        else
        {
            printf("删除的是根节点，id为：%d，数据为：%d\n", node->id, node->data);
            delete_link_root_node(node);
        }
    }
    else
    {
        printf("对不起，你要删除的节点不存在\n");
    }

     printf("执行删除操作过后的节点数为：%d\n\n\n", get_node_nums());

     printf("查询操作，请输入你要查询的节点的id：");
     int searchId =0;
     scanf("%d", &searchId);


    node = search_link_node(searchId, &temp);
    if(node != 0)
    {
        if(0 == temp)
        {
            printf("查询的结果data的值为：%d\n", node->next->data);

        }
        else
        {
            printf("查询的结果data的值为：%d\n", node->data);
        }
    }
    else
    {
        printf("对不起，查询不到\n");
    }


    printf("\n**********正在为你打印节点，共有%d个节点需要打印，请稍等*************\n\n", get_node_nums());
    print_hash();
    printf("打印完成\n\n");


    return 0;
}


ElemType hash_function(ElemType id)
{
    ElemType pos = 0;
    pos = id % HASH_TABLE_LENGTH;
    return pos;
}

Link_Node_Ptr init_link_node(void)
{
    Link_Node_Ptr lnode;
    lnode = (Link_Node_Ptr)malloc(sizeof(Link_Node));
    lnode->next = NULL;
    return lnode;
}

Hash_Head_Ptr init_hash_head_node(void)
{
    Hash_Head_Ptr hnode;
    hnode = (Hash_Head_Ptr)malloc(sizeof(Hash_Head));
    hnode->next = NULL;
    return hnode;
}

void init_hash_table(void)
{
    ElemType i = 0;
    for(; i < HASH_TABLE_LENGTH; i++)
    {
        Hash_Table[i] = init_hash_head_node();
        Hash_Table[i]->next = NULL;
    }
}

void add_link_node(Link_Node_Ptr newnode)
{
    Link_Node_Ptr lnode;
    ElemType pos = 0;
    pos = hash_function(newnode->id);
    if(NULL == Hash_Table[pos]->next)
    {
        Hash_Table[pos]->next = newnode;
    }
    else
    {
        lnode = Hash_Table[pos]->next;
        while(lnode->next != NULL)
        {
            lnode = lnode->next;
        }
        lnode->next = newnode;
    }
}

Link_Node_Ptr search_link_node(ElemType id, ElemType *root)
{
    Link_Node_Ptr lnode;
    ElemType pos  = 0;
    pos = hash_function(id);
    lnode = Hash_Table[pos]->next;
    if(NULL == lnode)
    {
        return 0;
    }
    
    if(lnode->id == id)
    {
        *root = 1;
        return lnode;
    }
    else
    {
        *root = 0;
        while(lnode->next != NULL)
        {
            if(lnode->next->id == id)
            {
                return lnode;
            }
            else
            {
                lnode = lnode->next;
            }
        }
        return 0;
    }
}

void delete_link_node(Link_Node_Ptr node)
{
    Link_Node_Ptr dnode;
    dnode = node->next;
    node->next = dnode->next;
    free(dnode);
    dnode = NULL;
}

void delete_link_root_node(Link_Node_Ptr node)
{
    ElemType pos = 0;
    pos = hash_function(node->id);
    if(node !=NULL)
    {
        Hash_Table[pos]->next = node->next;
        free(node);
        node = NULL;
    }
}

ElemType get_node_nums(void)
{
    Link_Node_Ptr lnode;
    ElemType i = 0;
    ElemType nums = 0;
    for(; i < HASH_TABLE_LENGTH; i++)
    {
        lnode = Hash_Table[i]->next;
        while(lnode != NULL)
        {
            nums++;
            lnode = lnode->next;
        }
    }
    return nums;
}

Link_Node_Ptr get_node_of_index(ElemType index, ElemType *root)
{
    Link_Node_Ptr lnode;
    ElemType i = 0;
    ElemType nums = 0;
    for(; i < HASH_TABLE_LENGTH; i++)
    {
        lnode = Hash_Table[i]->next;
        if(NULL == lnode)
        {
            continue;
        }
        nums++;
        if(nums == index)
        {
            *root = 1;
            return lnode;
        }
        while(lnode->next != NULL)
        {
            nums++;
            if(nums == index)
            {
                *root = 0;
                return lnode;
            }
            lnode = lnode->next;
        }
    }
    return 0;
}

void drop_hash(void)
{
    Link_Node_Ptr lnode;
    ElemType i = 0;
    Link_Node_Ptr nodenext;
    for(; i < HASH_TABLE_LENGTH; i++)
    {
        lnode = Hash_Table[i]->next;
        while(1)
        {
            if(NULL == lnode)
            {
                Hash_Table[i]->next = NULL;
                break;
            }
            nodenext = lnode->next;
            free(lnode);
            lnode = nodenext;
        }
    }
}

void print_hash(void)
{
    Link_Node_Ptr lnode;
    ElemType i = 0;
    ElemType root = 0;
    ElemType counts = 0;
    counts = get_node_nums();
    for(i = 1; i <= counts; i++)
    {
        lnode = get_node_of_index(i, &root);
        if(lnode != 0)
        {
            sleep(2);
            if(root)
            {
                printf("第%d个节点，是根节点，id为：%d，data为：%d\n", i, lnode->id, lnode->data);
                continue;
            }
            else
            {
                printf("第%d个节点，是普通节点，id为：%d，data为：%d\n", i, lnode->next->id, lnode->data);
                continue;
            }
        }
    }
}


















