#-------------------------------------------------
#
# Project created by QtCreator 2016-05-10T21:34:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Base3
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    universebody.cpp \
    universecomposite.cpp \
    config.cpp \
    zodiac.cpp \
    universecomponentfactory.cpp \
    visitordisplay.cpp \
    fetchfurthestbodies.cpp \
    visibility.cpp \
    reset.cpp

HEADERS  += dialog.h \
    universecomponent.h \
    universecomposite.h \
    universebody.h \
    config.h \
    zodiac.h \
    universecomponentfactory.h \
    visitor.h \
    visitordisplay.h \
    fetchfurthestbodies.h \
    visibility.h \
    reset.h

FORMS    += dialog.ui

OTHER_FILES +=
