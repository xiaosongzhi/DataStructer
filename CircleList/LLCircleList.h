#ifndef __LLIST__
#define __LLIST__

//普通节点
typedef struct llist_node_st
{
    void *data;
    struct llist_node_st *pre;
    struct llist_node_st *next;
}DataNode;

//头结点
typedef struct
{
    int size;
    DataNode head;
}LLIST;
enum MODE
{
  HEADMODE = 0,
  TAILMODE
};

LLIST* llist_create(int size);
void llist_destroy(LLIST*);
int llist_insert(LLIST*,const void*data,int mode);
void llist_display(LLIST*);
void llist_delete();
void llist_find();
void llist_fetch();



#endif
