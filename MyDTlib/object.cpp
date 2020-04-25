#include "object.h"
#include <cstdlib>
#include <iostream>
using namespace std;
namespace MyDTlib{
Object::Object()
{

}

void *Object::operator new(size_t size) noexcept //异常规格说明,不会抛出任何异常
{                                               //即使失败只会返回一个异常
    DEBUG <<size<< endl;
    return malloc(size);
}
void Object::operator delete (void *p)
{
    DEBUG<< endl;
    free(p);
}
void *Object::operator new[] (size_t size) noexcept
{
    DEBUG<< size<<endl;
    return malloc(size);
}
void Object::operator delete[] (void* p)
{
    DEBUG<< endl;
    free(p);
}

}
