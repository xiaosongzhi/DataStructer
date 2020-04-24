#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H
#include "seqlist.h"

namespace MyDTlib{

template<typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;//顺序存储空间大小

public:
    DynamicList(int capacity)
    {
        try{
            this->m_array = new T[capacity];

            if(this->m_array != NULL)
            {
                this->m_length = 0;
                this->m_capacity = capacity;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough space");
            }
        }
        catch(NoEnoughMemoryException &e)
        {
            cout << e.location()<<"  "<<e.message()<<endl;
        }

    }


    virtual int capacity() const
    {
        return m_capacity;
    }

    //重置存储空间大小
    void resizeSpace(int capacity)
    {
        if(m_capacity != capacity)
        {
            try{
                T* array = new T[capacity];
                if(array != NULL)
                {
                    int length = (this->m_length < capacity ? this->m_length:capacity);

                    //将原有数据拷贝到新申请的空间中
                    for(int i = 0;i < length;i++)
                        array[i] = this->m_array[i];
                    //用于释放堆空间
                    T* temp = this->m_array;
                    //成员变量赋值
                    this->m_array = array;
                    this->m_capacity = capacity;
                    this->m_length = length;

                    delete[] temp;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"no enough space to resize DynamicList object");
                }
            }
            catch(NoEnoughMemoryException &e)
            {
                cout << e.message() << endl;
                cout << e.location() << endl;
            }
        }
    }

};

}


#endif // DYNAMICLIST_H
