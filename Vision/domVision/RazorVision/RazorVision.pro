QT += core
QT -= gui

CONFIG += c++11

TARGET = RazorVision
CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS  += -O2

TEMPLATE = app

INCLUDEPATH +=
LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_imgproc
#LIBS += `pkg-config opencv --libs`

#temp dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

INCLUDEPATH += include \
               ~/Downloads/opencv/

SOURCES += src/main.cpp \
    src/entities/vision/eye.cc \
    src/entities/vision/colorreceptor.cc

HEADERS += \
    include/entities/vision/eye.hh \
    include/entities/vision/colorreceptor.hh
