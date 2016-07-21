#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T10:53:58
#
#-------------------------------------------------

QT       += core gui sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = selective
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addenterprise.cpp \
    db.cpp

HEADERS  += mainwindow.h \
    addenterprise.h \
    db.h

FORMS    += mainwindow.ui \
    addenterprise.ui

DISTFILES += \
    icon.ico

RC_FILE = ico.rc


