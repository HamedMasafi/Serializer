QT += testlib gui widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH = ../../src/
TEMPLATE = app

SOURCES +=  tst_basic.cpp \
    ../../src/abstractserializer.cpp \
    ../../src/stringserializer.cpp \
    ../../src/binaryserializer.cpp

HEADERS += \
    ../../src/abstractserializer.h \
    ../../src/serializer_global.h \
    ../../src/stringserializer.h \
    ../../src/binaryserializer.h

RESOURCES += \
    res.qrc
