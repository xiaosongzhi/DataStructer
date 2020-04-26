#ifndef LINKLIST_H
#define LINKLIST_H
#include "list.h"
#include "object.h"
#include "exception.h"
#include <iostream>
using namespace std;
namespace MyDTlib{
//有头单链表
template<typename T>
class LinkList : public List<T>
{
protected:
    mutable struct Node : public Object
    {
        T value;//为了避免调用自定义类型的构造函数我们做如下处理
        Node* next;
    }m_header;
#if 0
    mutable struct : public Object //与const作用相反
    {
        char reserve[sizeof(T)];
        Node* next;
    }m_header;
#endif
    int m_length;

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node *dy)
    {
        delete  dy;
    }


public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
    }

    virtual bool insert(const T&e)//默认头插
    {
        return insert(m_length,e);
    }
    virtual bool insert(int i,const T&e)
    {
        bool ret = ((i >= 0)&&(i<=m_length));
        //此处有了长度，下边就不需要判断链表是否到尾了
        if(ret)
        {
            try{
                Node *node = new Node();

                if(node)
                {
                    Node *current = &m_header;
                    //先找插入位置的前一个节点
                    for(int p= 0;p < i;p++)
                    {
                        current = current->next;
                    }
                    node->next = current->next;
                    current->next = node;
                    node->value = e;
                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
                }
            }
            catch(NoEnoughMemoryException &e)
            {
                cout << e.location()<<endl;
                cout << e.message() <<endl;
            }
        }

        return ret;

    }
    virtual bool remove(int i)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            Node *current = &m_header;
            //寻找的都是要操作位置的前驱
            for(int p = 0;p < i;p++)
            {
                current = current->next;
            }
            Node *delNode = current->next;
            current->next = delNode->next;
            m_length--;
            delete delNode;

        }

        return ret;
    }
    virtual bool set(int i,const T& e)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            Node *current = &m_header;
            for(int p = 0;p < i;p++)
            {
                current = current->next;
            }
            current = current->next;
            current->value = e;
        }

        return ret;
    }
    virtual bool get(int i,T& e) const
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            Node *current = &m_header;
            for(int p = 0;p < i;p++)
            {
                current = current->next;
            }
            current = current->next;
            e = current->value;
        }
        return ret;
    }
    T& get(int i)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            Node *current = &m_header;
            for(int p = 0;p < i;p++)
            {
                current = current->next;
            }
            current = current->next;


            return current->value;
        }

    }
    virtual int length() const
    {
        return m_length;
    }
    virtual void clear()
    {
        while(m_header.next)
        {
            Node *delNode = m_header.next;
            m_header.next = delNode->next;
            m_length--;
//            delete delNode;
            destroy(delNode);
        }
    }

    void display()
    {
        Node *current = m_header.next;

        while(current != NULL)
        {
            try{
                cout << current->value << endl; //先遍历，再移位
                current = current->next;
            }catch(...)
            {
                cout <<"越界异常"<<endl;
            }
        }
    }

    ~LinkList()
    {
        clear();
    }
};


}
#endif // LINKLIST_H
