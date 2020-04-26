#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H
#include "linklist.h"

namespace MyDTlib{
template<typename T,int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef  typename LinkList<T>::Node Node;//使用typename区分是类型还是静态成员变量
    unsigned char m_space[sizeof(Node)* N];//在内存中开辟一段连续的内存
    int m_used[N];                         //用于标识该未知是否被占用

    struct SNode : public Node
    {
      void *operator new(unsigned int size,void *loc)
      {
          Q_UNUSED(size);
          return loc;
      }
    };

    Node *create()
    {
        SNode *ret = NULL;

        for(int i = 0; i < N;i++ )
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode();//在指定的内存空间上调用构造函数
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }

    void destroy(Node* pn)
    {
        SNode *space = reinterpret_cast<SNode*>(m_space);
        SNode *psn = dynamic_cast<SNode*>(pn);
        for(int i = 0;i <N ;i ++)
        {
            if(pn == space + i)
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }
public:
    StaticLinkList()
    {
        for(int i = 0 ;i < N;i++)
            m_used[i] = 0;
    }
    ~StaticLinkList()
    {
        this->clear();
    }

};

}

#endif // STATICLINKLIST_H
