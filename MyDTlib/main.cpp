#include <iostream>
#include "object.h"
#include "smartpoint.h"
#include "exception.h"
#include "seqlist.h"
#include "staticlist.h"
#include "dynamiclist.h"
#include "staticarray.h"
#include "dynamicarray.h"
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
    /*
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
*/
    /*
#if 0
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
#endif
*/
    /*
#if 0
    StaticList<int,5> l;

    for(int i = 0;i <5;i++)
    {
        l.insert(i,2*i);
    }
    cout << l.length()<<endl;

    l.remove(3);

    for(int i = 0;i < l.length();i++)
    {
        cout << l[i] <<" "<<i <<endl;
    }
#endif
*/

#if 0
    DynamicList<int> l(5);

    for(int i = 0;i <5;i++)
    {
        l.insert(i,2*i);
    }
    cout << l.length()<<endl;

    for(int i = 0;i < l.length();i++)
    {
        cout << l[i] <<" "<<i <<endl;
    }

    l.resizeSpace(10);

    l.insert(5,10); //此处的插入不能在随意的位置,只能在0--length的范围内

    for(int i = 0;i < l.length();i++)
    {
        cout << l[i] <<" "<<i <<endl;
    }
#endif
#if 0
    StaticArray<int ,5> s1;
    for(int i = 0;i < 5;i++)
    {
        s1[i] = i*i;
    }

    for(int j = 0;j < s1.length();j++)
    {
        cout<<s1[j]<<endl;
    }

    StaticArray<int ,5> s2 = s1;

    s2.set(2,10);
    s2.set(3,10);



    for(int j = 0;j < s2.length();j++)
    {
        cout<<s2[j]<<endl;
    }
#endif

    DynamicArray<int> da(10);
    for(int i = 0;i < da.length();i++)
    {
        da[i] = i*3;
    }
    DynamicArray<int> db(da);
    da.resize(5);
    for(int i = 0;i < da.length();i++)
    {
        cout << i << "  "<<da[i] << endl;
    }
    cout <<"-----------------"<<endl;
    db.resize(15);
    for(int i = 0;i < db.length();i++)
    {
        cout << i << "  "<<db[i] << endl;
    }
    db[20] = 10;

    return 0;
}
