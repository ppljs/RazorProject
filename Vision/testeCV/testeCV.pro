QT += core
QT -= gui

CONFIG += c++11

TARGET = testeCV
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_core

SOURCES += main.cpp
