#include "seqlist.h"
namespace MyDTlib{

#if 0

//明确一下 @1   i从0开始，m_length为线性表的有效长度
// 0 1 2 3 4 5 6 7 8   m_length = 9; i可以取0-9，当为0时表示头插
//当为9时表示尾插
bool SeqList::insert(int i,const T&e)
{
    bool ret = (i>= 0) && (i <= m_length);  //i 可以取到 m_length

    ret = ret &&(m_length < capacity());    //不能超界

    if(ret)
    {   //                          此处必须有等号，将第i个位置空出
        for(int index = m_length-1;index >= i;index--)
        {
            m_array[index+1] = m_array[index];
        }
        m_array[i] = e;
        m_length++;
    }
    return ret;
}
bool SeqList::remove(int i)
{
    bool ret = (i>= 0) && (i < m_length);  //i 取不到 m_length

    if(ret)
    {
        for(int index = i;index < m_length;index++)
        {
            m_array[index] = m_array[index+1];
        }
        m_length--;
    }
    return ret;
}
bool SeqList::set(int i,const T& e)
{
    bool ret = (i>= 0) && (i < m_length);  //i 取不到 m_length

    if(ret)
        m_array[i] = e;

    return ret;

}
bool SeqList::get(int i,T& e) const
{
    bool ret = (i>= 0) && (i < m_length);  //i 取不到 m_length

    if(ret)
    {
        e = m_array[i];
    }

    return ret;
}
int SeqList::length() const
{
    return m_length;
}
void SeqList::clear()
{
    m_length = 0;
}

//数组访问方式
T& SeqList::operator[](int i)
{
    if((i >= 0) && (i < m_length-1))
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"out of index");
    }
}
T SeqList::operator[](int i) const
{
    return (const_cast<SeqList<T>&>(*this))[i];
}
#endif
}
