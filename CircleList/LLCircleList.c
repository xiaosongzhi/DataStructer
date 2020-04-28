#include "LLCircleList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
//创建只包含头结点的双向环链
LLIST* llist_create(int size)
{
    LLIST *headNode = malloc(sizeof(*headNode));
    if(headNode == NULL)
    {
        return NULL;
    }

    headNode->size = size;
    headNode->head.data = NULL;
    //此处指向的是LLIST的节点位,而不是指向LLIST的起始位
    headNode->head.next = &(headNode->head);
    headNode->head.pre = &(headNode->head);

    return new;

}
void llist_destroy(LLIST* ptr)
{
    DataNode *curr,*node;

    curr = ptr;
    //循环条件：游标不能等于头结点中的Node
    while(curr->next != &(ptr->head))
    {
        node = curr->next;
        free(curr->data);
        free(curr);

        curr = node;
    }
    //最后释放头结点
    free(ptr);

}
int llist_insert(LLIST* ptr,const void*data,int mode)
{
    DataNode *newNode = malloc(sizeof(*newNode));
    if(newNode == NULL)
    {
        return -1;
    }

    newNode->data = malloc(ptr->size);
    if(newNode->data == NULL)
    {
        return -2;
    }

    memcpy(newNode->data,data,ptr->size);

    switch(mode)
    {
    case HEADMODE://头插
        newNode->pre = &(ptr->head);
        newNode->next = ptr->head.next;
        newNode->pre->next = newNode;
        newNode->next->pre = newNode;
        break;
    case TAILMODE://尾插
        newNode->next = &(ptr->head);
        newNode->pre = ptr->head.pre;
        newNode->pre->next = newNode;
        newNode->next->pre = newNode;
        break;
    default:
        return -3;
        break;
    }

    return 0;
}
void llist_display(LLIST*)
{

}
