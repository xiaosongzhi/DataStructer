#include "exception.h"

using namespace std;

namespace MyDTlib{
Exception::Exception(const char* message)
{
//    m_message = const_cast<char*>(message);
    init(NULL,message,0);
}
Exception::Exception(const char*file,int line)
{
    init(file,NULL,line);
}
Exception::Exception(const char*message,const char*file,int line)
{
    init(file,message,line);
}
Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}
Exception& Exception::operator=(const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}
void Exception::init(const char*file,const char*message,int line)
{
    m_message = strdup(message);//该函数用于在堆中创建一片内存,用于拷贝保存

    if(file != nullptr)
    {
        char sl[16] = {0};
        itoa(line,sl,10);//将int转成char存放在字符数组中
        m_location = static_cast<char*>(malloc(strlen(file) + strlen(message) + 2));
        m_location = strcpy(m_location,file);
        m_location = strcat(m_location,":");
        m_location = strcat(m_location,sl);

    }
    else {
        m_location = nullptr;
    }
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}
Exception::~Exception() // 纯虚析构函数函数体
{
    delete  m_message;
    delete m_location;
}
}
