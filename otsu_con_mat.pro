QT += core
QT -= gui

TARGET = otsu_con_mat
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
LIBS += `pkg-config opencv --libs` -lm
HEADERS += \
    imagen.h \
    matrix.h \
    otsu.h

