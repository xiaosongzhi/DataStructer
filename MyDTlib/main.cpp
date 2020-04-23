#include <iostream>
#include "object.h"
#include "smartpoint.h"
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

class TestSmartPoint
{
public:
  TestSmartPoint()
  {
      DEBUG<<endl;
  }

  ~TestSmartPoint()
  {
      DEBUG<<endl;
  }

};


int main()
{
#if 0
    Object *obj1 = new Test();
    Object *obj2 = new Child();

    cout << obj1 <<endl;
    cout << obj2 <<endl;

    delete obj1;
    delete obj2;
#endif
    SmartPoint<TestSmartPoint> sp = new TestSmartPoint();

    SmartPoint<Test> st = new Test();

    return 0;
}
