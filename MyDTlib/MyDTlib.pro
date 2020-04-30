TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
        main.cpp \
        object.cpp \
    exception.cpp \
    seqlist.cpp

HEADERS += \
    CircleList.h \
    Pointer.h \
    SharedPointer.h \
    StaticLinkList.h \
    logfile.h \
    object.h \
    smartpoint.h \
    exception.h \
    list.h \
    seqlist.h \
    staticlist.h \
    dynamiclist.h \
    array.h \
    staticarray.h \
    dynamicarray.h \
    linklist.h
