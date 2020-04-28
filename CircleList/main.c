#include <stdio.h>
#include <stdlib.h>
#define LISTSIZE 8

//无头循环单链表
typedef struct node_st
{
    int data;
    struct node_st *next;

}Node;

Node* createCircleList(int num)
{
    //首先创建第一个节点
    Node *me = malloc(sizeof(*me));
    Node *newNode,*curr;
    if(me == NULL)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    int i = 1;
    me->data = 1;
    me->next = me;//自身构成环

    i++;
    curr = me;
    for(;i <= num;i++)
    {
        newNode = malloc(sizeof(*newNode));
        if(newNode == NULL)
        {
            free(me);
            return NULL;
        }
        //新节点初始化
        newNode->data = i;
        newNode->next = me;//       咬住首节点

        //将新的节点接入环内
        curr->next = newNode;    //此步操作已构成huan
        curr = newNode;         //移动curr节点，使其一直跟随最新节点
    }

    return me;

}
//遍历链表
void circleShow(Node *list)
{
    if(list != NULL)
    {
        Node* curr = list;

        while(curr->next != list)
        {
            printf("%d  ",curr->data);
            curr = curr->next;
        }
        printf(" %d \n",curr->data);
    }

}
//list--给定链表   num数的数字  s从第s个开始
void killJose(Node** list,int num,int s)
{
    //隔num-1个删一个
    //逻辑，首先找到要删除节点的前驱，然后在删除要删除的节点
    Node *curr = *list,*node;//代替me移动

    for(int j = 0;j < s;j++)
    {
        curr = curr->next;
    }

    int i = 1;

    while(curr!= curr->next) //只剩一个节点
    {
        if(1) //该if中的内容指的是只循环了一次
        {
            while(i < num)
            {
                node = curr;
                curr = curr->next;  //curr总是node的后一个节点
                i++;
            }
            //要删的节点是curr,它的前驱是node，我的目的是free(curr),但是在free之前要将node连接到curr->next
            printf("%d ",curr->data);
            node->next = curr->next;    //跳过curr节点
            free(curr);

            //开始下一轮
            curr = node->next;
            i = 1; //从新开始从1计数
        }
        printf("\n");
    }
    *list = curr;
}


int main()
{
    printf("Hello World!\n");
    Node *list = createCircleList(LISTSIZE);
    circleShow(list);
    printf("-------------------------\n");
    killJose(&list,3,3);  //约瑟夫杀人环
    circleShow(list);


    return 0;
}
