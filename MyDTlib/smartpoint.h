#ifndef SMARTPOINT_H
#define SMARTPOINT_H
#include <iostream>
#include "logfile.h"
using namespace std;

namespace MyDTlib{

template<typename T>
class SmartPoint
{
public:
    SmartPoint(T* p = NULL)
    {
        m_pointer = p;
    }

    SmartPoint(const SmartPoint<T> &obj)
    {
        m_pointer = obj.m_pointer;
        (const_cast<SmartPoint<T>&>(obj)).m_pointer = NULL;
    }

    SmartPoint<T>& operator=(const SmartPoint<T>& obj)
    {
        if(this != &obj)
        {
            delete m_pointer;
            m_pointer = obj.m_pointer;
            const_cast<SmartPoint<T>&>(obj).m_pointer;
        }
    }

    T* operator->()
    {
        return m_pointer;
    }

    T& operator*()
    {
        return *m_pointer;
    }

    bool isNull()
    {
        return (m_pointer == NULL);
    }

    T* get()
    {
        return m_pointer;
    }

    ~SmartPoint()
    {
        if(m_pointer)
        {
            delete m_pointer;
        }
    }

private:
    T *m_pointer;
};
}

#endif // SMARTPOINT_H
