# Copyright goes to Dave Smith
# for the original version of this sample program.

TARGET = ChatClient
TEMPLATE = app
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# This gives us access to the Qt socket classes (QTcpSocket)
QT += network

CONFIG += c++11

# This bundles any images we want right into our executable, so
# we do not have to ship any image files with our installer or RPM
# or deb package or whatever:
RESOURCES += images.qrc

FORMS   += MainWindow.ui 

HEADERS += MainWindow.h 

SOURCES += MainWindow.cpp \
           main.cpp

