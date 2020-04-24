#ifndef STATICLIST_H
#define STATICLIST_H
#include "seqlist.h"

namespace MyDTlib{

template<typename T,int N>
class StaticList : public SeqList<T>
{
protected:
    T m_space[N];
public:
    StaticList()
    {
        this->m_array = m_space;
        this->m_length = 0;
    }

    virtual int capacity() const
    {
        return N;
    }
};

}
#endif // STATICLIST_H
