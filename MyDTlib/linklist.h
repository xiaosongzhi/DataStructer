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
    //为了遍历新增  游标  元素
    //1.在遍历开始前将游标指向位置为0的数据元素
    //2.获取游标指向的数据元素
    //3.通过节点中的next指针移动游标
    //设计函数 move()--将游标定位到目标位置   next()移动游标
    //current()获取游标所指向的数据元素  end()游标是否到大尾部
    Node* m_current;
    int m_step; //游标每次移动节点的数目

    //获取位置
    Node *position(int i)
    {
        Node *ret = reinterpret_cast<Node*>(&m_header);

        for(int p = 0;p < i;p++)    //i = 0也可取到
        {
            ret = ret->next;
        }

        return ret;
    }
public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
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
    virtual bool get(int i,T& e)
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
    T& get(int i)   //获取某个位置的值
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
    virtual int find(const T& e)    //查找某个元素返回下标
    {
        int ret = -1;
        Node *slider = this->m_header.next;
        for(int i = 0;i < this->m_length;i++)
        {
            if(e == slider->value)
            {
                ret = i;
                break;
            }
            slider = slider->next;
        }

        return ret;
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
    void display( int times)
    {
        Q_UNUSED(times);
        for(this->move(0);!this->end();this->next())
        {
            cout << this->current() << endl;
        }
    }
/////////////////////////////////////
    /**游标实现函数---使m_current获取到当前位置的数据****/

    bool move(int i,int step = 1) //移动到指定的第i的位置，默认每次移动1步
    {
        bool ret = (i < m_length && i >= 0);

        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;

    }

    bool end() //游标是否到尾部
    {
        return (m_current == NULL);
    }

    T current() //获取到游标所在位置的数据
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"can not find the value");
        }

    }

    bool next() //将游标移动 m_step 步，此处使用m_step的好处是可以在已知的情况下加快查找速度
    {           //但实际上效率并没有变,因为即使m_step != 1,也是将m_step分解成一步一步移动
        int i = 0;
        while(i < m_step && !end())
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    ~LinkList()
    {
        clear();
    }
};


}
#endif // LINKLIST_H
