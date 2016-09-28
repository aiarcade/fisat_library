#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T21:38:38
#
#-------------------------------------------------

QT       += core gui  sql opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kiosk
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    searchwidget.cpp \
    mapwidget.cpp \
    glwidget.cpp \
    proximityreader.cpp \
    bubble.cpp \
    dbhelper.cpp \
    glmap.cpp

HEADERS  += \
    mainwindow.h \
    searchwidget.h \
    mapwidget.h \
    glwidget.h \
    proximityreader.h \
    bubble.h \
    dbhelper.h \
    glmap.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    files.qrc

DISTFILES +=
