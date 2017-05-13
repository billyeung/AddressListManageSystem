#-------------------------------------------------
#
# Project created by QtCreator 2015-12-31T16:03:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddressListManageSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addrlist.cpp \
    abdlg.cpp \
    helpdlg.cpp \
    newcontact.cpp \
    deletedlg.cpp \
    modcontact.cpp \
    errdlg.cpp

HEADERS  += mainwindow.h \
    addrlist.h \
    abdlg.h \
    helpdlg.h \
    newcontact.h \
    deletedlg.h \
    modcontact.h \
    errdlg.h

FORMS    += mainwindow.ui \
    abdlg.ui \
    helpdlg.ui \
    newcontact.ui \
    deletedlg.ui \
    modcontact.ui \
    errdlg.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    resource.rc

RC_FILE = resource.rc
