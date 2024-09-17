TEMPLATE = app
TARGET = strtools_test
DEPENDPATH += .
INCLUDEPATH += ../../src
CONFIG += debug
QT += core network xml
QMAKE_CXXFLAGS += -std=c++11

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

include(../../VERSION)
DEFINES+=VERSION=\\\"$$VERSION\\\"

HEADERS += ../../src/strtools.h 

SOURCES += strtools_test.cpp \
           ../../src/strtools.cpp 

