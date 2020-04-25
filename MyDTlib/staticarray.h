#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "array.h"

namespace MyDTlib{
template<typename T,int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];
public:
    StaticArray()
    {
        this->m_array = m_space;    //此处为啥这么赋值
    }
    //可以实现数组拷贝构造
    StaticArray(const StaticArray<T,N>& obj)
    {
        this->m_array = obj.m_array;

        for(int i = 0;i < N;i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }
    //实现数组赋值
    StaticArray<T,N>& operator=(const StaticArray<T,N>&obj)
    {
        if(this != &obj)
        {
            for(int i = 0;i < N;i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return *this;
    }
    //数组自带长度属性
    int length()
    {
        return N;
    }
};

}
#endif // STATICARRAY_H
