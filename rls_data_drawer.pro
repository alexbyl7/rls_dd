#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T11:34:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rls_dd
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    parser.cpp \
    drawer.cpp

HEADERS  += widget.h \
    parser.h \
    rls_header.h \
    drawer.h

FORMS    += widget.ui
