QT += testlib gui widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH = ../../src/
TEMPLATE = app


include(../../src/src.pri)

SOURCES += \
    boo.cpp \
    foo.cpp \
    tst_object.cpp

HEADERS += \
    boo.h \
    foo.h
