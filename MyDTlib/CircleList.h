#ifndef CIRCLELIST_H
#define CIRCLELIST_H
#include "linklist.h"

namespace MyDTlib{
template<class T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;//定个别名
    //连接首尾
    void last_to_first()
    {
        (last()->next) = (this->m_header).next;
    }

    Node* last()
    {
        return (this->position(this->m_length-1))->next;
    }
    //因为是循环链表，所以位置可能会大于长度，通过取余确定位置
    int mod(int index)
    {
        return ((this->m_length == 0) ? 0 : (index % this->m_length));
    }

public:

    bool insert(const T& e)
    {
        return insert(this->m_length,e);
    }
    bool insert(int i ,const T& e)
    {
        bool ret = true;
        i = i % (this->m_length + 1);//注意小细节，此处要能取到m_length,所以要在此加 1

        //先当单链表使用进行插入
        ret = LinkList::insert(i,e);//调用父类函数，实现子类函数 ？？？？？？
        //首元素插入比较特殊,插入完成后需要进行收尾相接
        if(ret && (i == 0)) //特殊的首元素插入
        {
            last_to_first();
        }
        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;
        i = mod(i);

        if(0 == i)
        {
            Node *toDel = this->m_header.next;

            if(toDel == NULL)
            {
                return false;
            }
            else
            {
                this->m_header.next = toDel->next;
                this->m_length--;

                if(this->m_length > 0)
                {
                    last_to_first();

                    if(this->m_current == toDel)
                    {
                        this->m_current = this->m_current->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }

                this->destroy(toDel);
            }
        }
        else    //删除非首节点
        {
            ret = LinkList<T>::remove(i);
        }
        return ret;
    }

    bool set(int i,const T& e)
    {
        return LinkList<T>::set(mod(i),e);
    }

    T& get(int i)
    {
        return LinkList<T>::get(mod(i));
    }
    bool get(int i,T& e)
    {
        return LinkList<T>::get(mod(i),e);
    }

    int find(const T&e)
    {
        int ret = -1;
        Node* slider = this->m_header.next;

        for(int i =0 ;i < this->length();i++)
        {
            if(slider->value == e)  //即使此处抛出异常，亦不会影响链表的循环特性
            {
                ret = i;
                break;
            }
            slider = slider->next;
        }
        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);          //为了效率删除第一个节点，而不是第0个
        }
        if(this->m_length == 1) //删除首节点
        {
            Node * toDel = this->m_header.next;

            this->m_header.next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(toDel);
        }

    }

    void dispaly()
    {
        if(m_length > 0)
        {
            Node *slider = this->m_header.next;

            while( ((slider->next) != (this->m_header.next)))
            {
                cout << slider->value << endl;
                slider = slider->next;
            }
            cout << slider->value << endl;
        }
    }

    ~CircleList()
    {
        clear();
    }
};

}


#endif // CIRCLELIST_H
