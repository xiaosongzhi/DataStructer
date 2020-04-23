#include <iostream>
#include "object.h"

using namespace std;
using namespace MyDTlib;
//32位大小为8  一个int + 虚函数指针
class Test : public Object
{
  public:
    int x;

     ~Test()
    {
        DEBUG<< endl;
        x = 10;
    }
};

//32位大小为16  三个int + 虚函数表
class Child : public Test
{
  public:
    int y;
    int z;

    ~Child()
    {
        DEBUG<< endl;
        y = 1;
        z = 2;
    }
};

int main()
{

    Object *obj1 = new Test();
    Object *obj2 = new Child();

    cout << obj1 <<endl;
    cout << obj2 <<endl;

    delete obj1;
    delete obj2;

    return 0;
}
