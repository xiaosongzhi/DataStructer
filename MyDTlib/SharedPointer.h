#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H
#include <iostream>
using namespace std;
#include "exception.h"
#include "Pointer.h"
//设计原则 ： 使用计数机制,记录指针数量
//计数机制确保多个智能指针能指向同一片内存空间
//堆对象的生命周期由智能指针进行管理
//SharedPointer最大程度的模拟了原生指针的行为
namespace MyDTlib{
template<typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int *m_ref; //此处不能使用静态属性，因为计数的数量并不是使用该类实例化了
    //多少对象,二十针对该对象进行了多少次赋值以及析构，只是针对此对象的，并不是针对此类

public:

    SharedPointer(T *p = NULL) :m_ref(NULL)
    {
        try{
            if(p)
            {
                this->m_ref = new int;
                if(this->m_ref)
                {
                    *(this->m_ref) = 1;
                    this->m_pointer = p;
                }

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
            }
        }
        catch(NoEnoughMemoryException &e) {
            cout <<e.location()<<endl;
            cout <<e.message() << endl;
        }
    }
    SharedPointer(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)
            (*(this->m_ref))++;

    }

    SharedPointer& operator=(const SharedPointer<T>& obj)
    {
        //先清空
        clear();
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)
            (*(this->m_ref))++;

        return *this;
    }

    void clear()//将当前指针置空
    {
        T *toDel = this->m_pointer;
        int *ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;

        if(ref) //判断当前是否有一个合法的计数变量
        {
            (*ref)--;

            if(0 == *ref)
            {
                delete ref;
                delete toDel;   //释放堆空间
            }
        }

    }
//    bool operator==(const SharedPointer<T>& l1,const SharedPointer<T>& l2);
    ~SharedPointer();

};


//问题 const对象不能调非const非成员函数？？
template<typename T>
bool operator==(const SharedPointer<T>& l1,const SharedPointer<T>& l2)
{
    return (l1.get() == l2.get());
}
template<typename T>
bool operator!=(const SharedPointer<T>& l1,const SharedPointer<T>& l2)
{
    return (l1 == l2);
}

}
#endif // SHAREDPOINTER_H
