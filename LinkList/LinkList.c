#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

typedef Node *LinkList;     //定义一个LinkList

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

/*     寻找第一个与e满足的元素       */
/*         初始条件L已存在          */
Status LocateElm(LinkList L, ElmType e)
{
    int i = 1;
    LinkList p = L->next;

    while(p)
    {     
        if(p->data == e)            //如果节点里有相同的元素
        return i;                   //返回位置
        p = p->next;                //没有继续往下搜索
        i++;                        //位置+1
    }
    return ERROR;
}

/*          删除表中的某个元素                  */
Status ListDelete(LinkList *L, int i, ElmType* e)
{
    int j = 1;
   LinkList p,q;

    p = *L;
    while(p->next && j<i)
    {
        p = p->next;
        j++;
    }
    if(!p->next || j>i)
    return ERROR;

    q = p->next;                    /*将后继的值给q*/
    p->next = q->next;              /*将q后继的值p的后继     p->next = p->next->next*/

    *e = q->data;                   /*返回删除元素*/
    free(q);                        /*释放空间*/
    return OK;
}

/* 头插法随机从产生N个随机数  */
Status CreateListHead(LinkList *L, int n)
{
    LinkList q;
    //创建表头
    srand(time(0));
   *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    while(n--)
    {
        q = (LinkList)malloc(sizeof(Node));
        q->data = rand() % 100 + 1;
        q->next = (*L)->next;
        (*L)->next = q;
    }

    return OK;

}

/*      尾插法随机产生N个随机数         */
Status CreateListTail(LinkList *L,int n)
{
    LinkList q,r;
    //生成随机数
    srand(time(0));
    //创建表头
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;
    while(n--)
    {
        //创建节点
        q = (Node *)malloc(sizeof(Node));
        q->data = rand() % 100 + 1;
        r->next = q;
        r = q;
    }  

    return OK;
}

int main()
{
    int i;
    Status sta,k;         //查看状态变量
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

    for(i=9;i<=11;i++)
    {
        k = LocateElm(L,i);
        if(k)
            printf("第%d个的元素为%d\n",k,i);
         else
            printf("没有值为%d的元素\n",i);
    }

    k = ListLength(L);
    printf("LinkLenght(L):%d \n",ListLength(L));
    for(i=k+1; i>=k; i--)
    {
        //删除第i行的数据      //e返回删除元素
        sta = ListDelete(&L,i,&e);
        if(sta == ERROR)
            printf("删除%d的元素失败\n",i);
        else
            printf("删除第%d的元素为%d\n",i,e);
    }
    printf("依次输出L元素:");
    ListTraverse(L);

    i = 5;
    ListDelete(&L,5,&e);
    printf("删除第%d的元素为%d",i,e);

    sta = ClearList(&L);
    printf("清空后L后:ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建表格头插法L.data\n");
    ListTraverse(L);

    sta = ClearList(&L);
    printf("清空后L后:ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建表格尾插法L.data\n");
    ListTraverse(L);
}
