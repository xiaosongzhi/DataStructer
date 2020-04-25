#ifndef OBJECT_H
#define OBJECT_H
#include "logfile.h"
namespace MyDTlib{
//typedef  unsigned long long size_t;
class Object
{
public:
    Object();

    void *operator new(size_t size) noexcept;
    void operator delete (void *p);
    void *operator new[] (size_t size) noexcept;
    void operator delete[] (void* p);
    virtual ~Object()
    {

    };
};
}

#endif // OBJECT_H
