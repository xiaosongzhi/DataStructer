#ifndef SMARTPOINT_H
#define SMARTPOINT_H
#include <iostream>
#include "logfile.h"
#include "Pointer.h"
using namespace std;

//设计原则：同一片堆空间只能由一个智能指针的指向
namespace MyDTlib{

template<typename T>
class SmartPoint : public Pointer<T>
{
protected:
//    T *m_pointer;
public:
    SmartPoint(T* p = NULL) : Pointer<T>(p)
    {

    }

    SmartPoint(const SmartPoint<T> &obj)
    {
        this->m_pointer = obj.m_pointer;
        (const_cast<SmartPoint<T>&>(obj)).m_pointer = NULL;
    }

    SmartPoint<T>& operator=(const SmartPoint<T>& obj)
    {
        if(this != &obj)
        {
            T *temp = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPoint<T>&>(obj).m_pointer;
            delete temp;
        }
    }

    ~SmartPoint()
    {
        if(this->m_pointer)
        {
            delete this->m_pointer;
        }
    }


};
}

#endif // SMARTPOINT_H
