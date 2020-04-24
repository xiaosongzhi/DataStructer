#ifndef SEQLIST_H
#define SEQLIST_H
#include "list.h"
#include "exception.h"
namespace MyDTlib{
template<typename T>
class SeqList : public List<T>
{
protected:
    T *m_array;//顺序存储空间
    int m_length;//当前线性表长度
public:
    virtual bool insert(const T&e)//默认尾插
    {
       return insert(m_length,e);
    }
    virtual bool insert(int i,const T&e)
    {
        bool ret = (i>= 0) && (i <= m_length);  //i 可以取到 m_length

        ret = ret &&(m_length < capacity());    //不能超界

        if(ret)
        {   //                          此处必须有等号，将第i个位置空出
            for(int index = m_length-1;index >= i;index--)
            {
                m_array[index+1] = m_array[index];
            }
            m_array[i] = e;
            m_length++;
        }
        return ret;
    }
    virtual bool remove(int i)
    {
        bool ret = (i>= 0) && (i < m_length);  //i 取不到 m_length

        if(ret)
        {
            for(int index = i;index < m_length;index++)
            {
                m_array[index] = m_array[index+1];
            }
            m_length--;
        }
        return ret;
    }
    virtual bool set(int i,const T& e)
    {
        bool ret = (i>= 0) && (i < m_length);  //i 取不到 m_length

        if(ret)
            m_array[i] = e;

        return ret;
    }
    virtual bool get(int i,T& e) const
    {
        bool ret = (i>= 0) && (i < m_length);  //i 取不到 m_length

        if(ret)
        {
            e = m_array[i];
        }

        return ret;
    }
    virtual int length() const
    {
        return m_length;
    }
    virtual void clear()
    {
        m_length = 0;
    }

    //数组访问方式
    T& operator[](int i) //针对非constd对象
    {
        try{
            if((i >= 0) && (i < m_length))
            {
                return m_array[i];
            }
            else
            {
                THROW_EXCEPTION(IndexOutOfBoundsException,"out of index");
            }
        }
        catch(IndexOutOfBoundsException &e)
        {
            cout << e.message() <<endl;
            cout << e.location() << endl;
        }
    }
    T operator[](int i) const //针对const 对象
    {
        return (const_cast<SeqList<T>&>(*this))[i];
    }
    //顺序存储空间容量
    virtual int capacity() const = 0;

};

}

#endif // SEQLIST_H
