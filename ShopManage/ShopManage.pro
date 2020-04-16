#-------------------------------------------------
#
# Project created by QtCreator 2020-04-06T14:54:02
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShopManage
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


SOURCES += \
    frmnavlistviewform.cpp \
    main.cpp \
    navlistview.cpp \
    widget.cpp \
    changepassword.cpp \
    intable_model.cpp \
    mylineedit.cpp \
    backview.cpp

HEADERS += \
    frmnavlistviewform.h \
    navlistview.h \
    widget.h \
    changepassword.h \
    intable_model.h \
    mylineedit.h \
    backview.h

FORMS += \
    frmnavlistview.ui \
    frmnavlistviewform.ui \
    widget.ui \
    changepassword.ui \
    backview.ui

RESOURCES += \
    rc.qrc

DISTFILES +=
