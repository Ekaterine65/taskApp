QT += testlib
QT += network
QT += sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../server/database.cpp \
    ../server/functions.cpp \
    ../server/mytcpserver.cpp \
    unit_tests.cpp

HEADERS += \
    ../server/database.h \
    ../server/mytcpserver.h \
