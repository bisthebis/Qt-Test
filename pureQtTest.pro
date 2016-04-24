#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T21:32:32
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pureQtTest
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
    basicsurface.cpp \
    mainwindow.cpp \
    camera.cpp

HEADERS  += \
    basicsurface.h \
    mainwindow.h \
    camera.h

FORMS += \
    mainwindow.ui

