QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    list_of_edges.cpp \
    list_of_edges_2.cpp \
    main.cpp \
    mainwindow.cpp \
    regform.cpp \
    singleclient.cpp \
    tasks.cpp \
    teachertable.cpp

HEADERS += \
    client.h \
    list_of_edges.h \
    list_of_edges_2.h \
    mainwindow.h \
    regform.h \
    singleclient.h \
    singleton.h \
    tasks.h \
    teachertable.h

FORMS += \
    list_of_edges.ui \
    list_of_edges_2.ui \
    mainwindow.ui \
    regform.ui \
    tasks.ui \
    teachertable.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
