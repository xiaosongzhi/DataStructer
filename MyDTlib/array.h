#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include "object.h"
#include "exception.h"

using namespace std;

namespace MyDTlib{
//在抽闲Array中并不会开辟空间存放数组
//存放数据的操作放在子类中进行实现
template<typename T>
class Array : public Object
{
protected:
    T * m_array;    //此处的指针就是为了访问操作用的吗
public:
    virtual bool set(int i,const T&e)
    {
        bool ret = ((i >= 0) && (i < length()));

        if(ret)
        {
            m_array[i] = e;
        }

        return ret;
    }
    virtual bool get(int i,T&e) //const //此处加const就会报错
    {
        bool ret = ((i >= 0) && (i < length()));
        if(ret)
        {
           e = m_array[i];
        }
        return ret;
    }
    T& operator[](int i)
    {
        bool ret = ((i >= 0) && (i < length()));
        try{
            if(ret)
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
            cout<<e.location()<<endl;
            cout<<e.message()<<endl;
        }

    }
    T operator[](int i)const
    {
        //去掉const属性，模板和强制转换还没弄太懂
        return (const_cast<Array<T>&>(*this))[i];
    }
    virtual int length() = 0;
};

}
#endif // ARRAY_H
