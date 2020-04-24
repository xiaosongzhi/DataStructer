#include <iostream>
#include "object.h"
#include "smartpoint.h"
#include "exception.h"
using namespace std;
using namespace MyDTlib;
//32位大小为8  一个int + 虚函数指针
class Test : public Object
{
  public:
    int x;

    virtual ~Test()
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

    virtual ~Child()
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
    SmartPoint<TestSmartPoint> sp = new TestSmartPoint();
    SmartPoint<Test> st = new Test();
#endif
    try {
        THROW_EXCEPTION(ArithmeticException,"HONG");
//        throw Exception("test error",__FILE__,__LINE__);
    }
    catch (InvalidParameterException &e) {
        DEBUG << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch (Exception &e) {
        DEBUG << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    cout << "I am end"<<endl;

    return 0;
}
