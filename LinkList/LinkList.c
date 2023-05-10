#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0;
#define TRUE 1

typedef int Status;
typedef int ElmType;
//创建LinkList
typedef struct Node     
{
    ElmType data;
    struct Node*  next;
}Node;

typedef Node* LinkList;     //定义一个LinkList

Status InitList(LinkList *L)                // 这是一个二级指针,用来指向头节点
{
    //产生一个头节点
   *L =(LinkList)malloc(sizeof(Node));    //开辟一个节点的大小
   if(*L == NULL)                         //判断空间是否申请成工
   return ERROR;
   else
   (*L)->next = NULL;

   return OK;
}

/*       求出表长           */
Status ListLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next;
    while(p != NULL)
    {
        i++;
    
        p = p->next;
    }

    return i;
}

/*          在i的位置插入元素           */
Status InsertList(LinkList *L,int i,ElmType e)
{
    int j = 1;
    LinkList p,s;
    p = *L;
    while(p && j<i)                 //寻找第i个节点
    {
        p=p->next;
        j++;
    }
    if(!p || j>i)                   //第一个元素不存在
        ERROR;
    s = (LinkList)malloc(sizeof(Node));     
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

/*      访问元素    */
void visit(ElmType e)
{
    printf("%d ",e);
}

/*          遍历表          */
Status ListTraverse(LinkList L)
{
    LinkList p = L->next;
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status ListEmpty(LinkList L)
{
    //判断表是否为空表
    LinkList p = L->next;
    if(!p)
    return TRUE;

    return FALSE;
}

/*       删除整表          */
Status ClearList(LinkList *L)
{
    LinkList q,p;
    
    //把头节点的下一个节点地址给q
    q = (*L)->next;
    while(q)
    {
        p = q->next;        //先把q的下一位节点给p  以防释放后寻找不到
        free(q);            //释放空间
        q = p;              //把下一个节点地址还给q,进行下一步释放
    }
    (*L)->next = NULL;      //所有销毁后头节点指向NULL 避免野指针

    return OK;
}

Status GetElm(LinkList L,int i,ElmType *e)
{
    int j = 1;
   LinkList p = L;

   while(p && j<=i)             //当p不为空表且j小于等于i
   {
        p = p->next;
        j++;
   }
   if(!p && j>i)                //如果p出来没有找到,或者j大于i
    return ERROR;

    *e = p->data;
    return OK;
}

int main()
{
    int i;
    Status sta;         //查看状态变量
    ElmType e;
    LinkList L;
    //初始化表格
    InitList(&L);
   printf("初始化节点后的长度%d",ListLength(L));

   for(i=1; i<=5; i++)
   {
        sta=InsertList(&L,1,i);
   }
   printf("在表头插入1~5个元素:L.data :");
   ListTraverse(L);

    printf("LinkLenght(L):%d \n",ListLength(L));

    sta = ListEmpty(L);
    printf("L是否为空:%d (1：是  0 否)\n",sta);

    sta = ClearList(&L);
    printf("清空链表后LinkLenght(L):%d \n",ListLength(L));
    sta = ListEmpty(L);
    printf("L是否为空:%d (1：是  0 否)\n",sta);

    for(i=1; i<=10; i++)
    {
         sta=InsertList(&L,i,i);
    }
    printf("在表尾插入1~10个元素:L.data:");
     ListTraverse(L);

     printf("LinkLenght(L):%d \n",ListLength(L));

    InsertList(&L,1,0);
    ListTraverse(L);
    printf("LinkLenght(L):%d \n",ListLength(L));

    GetElm(L,5,&e);
    printf("在L中的第5个元素为:%d\n",e);




}
