#-------------------------------------------------
#
# Project created by QtCreator 2019-04-04T00:52:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# This gives us access to the Qt socket classes (QTcpSocket)
QT += testlib
QT += network
TARGET = jatek
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    board.cpp \
    deck.cpp \
    player.cpp \
    domino.cpp \
    model.cpp \
    tablewidget.cpp \
    playerwidget.cpp \
    dominobutton.cpp \
    color.cpp \
    client.cpp \
    server.cpp

HEADERS += \
        widget.h \
    common.h \
    Deck.h \
    King.h \
    Player.h \
    Board.h \
    model.h \
    tablewidget.h \
    playerwidget.h \
    model.h \
    king.h \
    deck.h \
    domino.h \
    dominobutton.h \
    color.h \
    player.h \
    board.h \
    client.h \
    server.h \
    tester.h

FORMS += \
    widget.ui \
    playerwidget.ui

RESOURCES = resources/dominoSide.qrc \
    resources/crowns.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    jatek.pro
