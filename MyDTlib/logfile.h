#ifndef LOGFILE_H
#define LOGFILE_H

#include <QDebug>
#include <iostream>

#ifndef OUT_FORMAT
#define OUT_FORMAT "{ FILE:["<<__FILE__<<"] LINE:"<<__LINE__<<" func:"<<__func__<< " }: "
#endif

#ifndef DEBUG
#define DEBUG std::cout<<OUT_FORMAT
#endif

#ifndef WARNING
#define WARNING qWarning()<<OUT_FORMAT
#endif

#endif // LOGFILE_H
