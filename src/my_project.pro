#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T12:07:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_project
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    laws.cpp \
    integrate.cpp \
    drawgraphics.cpp \
    phaseportret.cpp \
    parameters.cpp \
    camprofile.cpp \
    phaseportret_rotating.cpp

HEADERS  += widget.h \
    laws.h \
    parameters.h \
    integrate.h \
    drawgraphics.h \
    phaseportret.h \
    camprofile.h \
    phaseportret_rotating.h

FORMS    += widget.ui
