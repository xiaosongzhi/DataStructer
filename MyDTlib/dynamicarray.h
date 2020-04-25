#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "array.h"
#include "exception.h"
namespace MyDTlib{
template<typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    //在堆空间中申请新的内存，并执行拷贝操作
    T* copy(T* array,int len,int newlen)
    {
        T *newarray = new T[newlen];
        if(newarray != NULL)
        {
            int size = newlen < len ? newlen : len;
            for(int i = 0; i< size;i++)
            {
                newarray[i] = array[i];
            }
        }
        return newarray;
    }
    //将指定的堆空间作为内部存储数组使用
    void update(T* array,int length)
    {
        if(array != NULL)
        {
            m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
        }
    }
    //对象构造时的初始化操作
    void init(T*array,int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
        }
    }
public:
    DynamicArray(int length)
    {

        try{
            init(new T[length],length);
            //////////////////////下面重构前
            /*
            this->m_array = new T[length];
            if(this->m_array!= NULL)
            {
                m_length = length;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
            }
            */
        }
        catch(NoEnoughMemoryException &e)
        {
            cout << e.location()<<endl;
            cout << e.message()<<endl;
        }
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        try {
            //代码重构
            T *array = copy(obj.m_array,obj.m_length,obj.m_length);
            init(array,obj.m_length);
            //////////////////////下面重构前
            /*
            this->m_array = new T[obj.m_length];
            if(this->m_array != NULL)
            {
                this->m_length = obj.m_length;
                for(int i = 0;i < obj.m_length;i++)
                {
                    this->m_array[i] = obj.m_array[i];
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
            }
            */

        } catch (NoEnoughMemoryException &e) {
            cout << e.location()<<endl;
            cout << e.message()<<endl;
        }
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& obj)
    {
        //赋值步骤
        if(this != &obj)
        {   //代码重构
            try{
                update(copy(obj.m_array,obj.m_length,obj.m_length),obj.m_length);
                /////////////////////////////////下面重构前
                /*
                    //1、开辟新空间
                    T *array = new T[obj.m_length];

                    if(array != NULL)
                    {
                        //2、给新开开辟的空间赋值
                        for(int i =0;i < obj.m_length;i++)
                        {
                            array[i] = obj.m_array[i];
                        }
                        //3、移位大法
                        T* temp = this->m_array;
                        this->m_array = array;
                        this->m_length = obj.m_length;
                        delete[] temp;
                    }
                    else {
                        THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
                    }
                    */
            }
            catch (NoEnoughMemoryException &e) {
                cout << e.location()<<endl;
                cout << e.message()<<endl;
            }
        }
        return *this;
    }


    void resize(int length)
    {
        if(length != m_length)
        {
            try {
                //代码重构
                T *array = copy(this->m_array,this->m_length,length);
                update(array,length);
                ////////////////////////////下面重构前
                /*
                T*array = new T[length];
                if(array != NULL)
                {   //首先获取要拷贝数据的大小
                    int size = this->m_length < length ? this->m_length : length;

                    for(int i =0; i < size;i++)
                    {
                        array[i] = this->m_array[i];
                    }

                    T* temp = this->m_array;
                    this->m_array = array;
                    this->m_length = length;

                    delete[] temp;
                }
                else {
                    THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
                }
                */
            } catch (NoEnoughMemoryException &e) {
                cout << e.location()<<endl;
                cout << e.message()<<endl;
            }
        }
    }

    virtual int length()
    {
        return m_length;
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }

};

}
#endif // DYNAMICARRAY_H
