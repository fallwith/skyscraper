QT += core network xml testlib
TEMPLATE = app
TARGET = settings_test
INCLUDEPATH += ../..

include(../../VERSION)
DEFINES+=VERSION=\\\"$$VERSION\\\"

QMAKE_POST_LINK += cp -f $$shell_quote($$shell_path($${PWD}/../../peas.json)) .; 
QMAKE_POST_LINK += cp -f $$shell_quote($$shell_path($${PWD}/../../platforms_idmap.csv)) .;

# Input
HEADERS += settings_test.h \
           ../../src/settings.h \
           ../../src/strtools.h \
           ../../src/platform.h \
           ../../src/cli.h
SOURCES += settings_test.cpp \
           ../../src/settings.cpp \
           ../../src/strtools.cpp \
           ../../src/platform.cpp \
           ../../src/cli.cpp
