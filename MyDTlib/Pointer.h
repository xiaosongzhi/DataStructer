#ifndef POINTER_H
#define POINTER_H
#include "object.h"
//智能指针抽象类
//使用规则
//1/只能用来指向堆空间中的单个变量(对象)
//2/不同类型的智能指针不能混用
//3/不要使用delete释放智能指针指向的堆空间

namespace MyDTlib{

template<typename T>
class Pointer : public Object
{
protected:
    T *m_pointer;
public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }
    T* operator->()
    {
        return m_pointer;
    }
    T& operator*()
    {
        return *m_pointer;
    }
    bool isNull() const
    {
        return (m_pointer == NULL);
    }
    const T* get()const
    {
        return m_pointer;
    }
    //此处没有重写自己的析构函数，就相当于继承自Object的虚析构函数
    //
};

}
#endif // POINTER_H
