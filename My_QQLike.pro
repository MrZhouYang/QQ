#-------------------------------------------------
#
# Project created by QtCreator 2018-07-04T15:57:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = My_QQLike
TEMPLATE = app

INCLUDEPATH += ./src/model \
            ./src/ui

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    src/ui/loginform.cpp \
    src/ui/moveableframelesswindow.cpp \
    src/ui/mainform.cpp \
    src/ui/collapseview.cpp \
    src/ui/collapseviewitem.cpp \
    src/ui/litteriem.cpp \
    src/model/singleton.cpp \
    src/model/config.cpp \
    src/ui/colorpickform.cpp \
    src/ui/registerdialog.cpp \
    src/model/sqliteoperate.cpp \
    src/ui/collapseviewitem_contact.cpp \
    src/model/data_pools.cpp \
    src/ui/chatform.cpp

HEADERS  += mainwindow.h \
    src/ui/loginform.h \
    src/ui/moveableframelesswindow.h \
    src/ui/mainform.h \
    src/ui/collapseview.h \
    src/ui/collapseviewitem.h \
    src/ui/litteriem.h \
    src/model/singleton.h \
    src/model/config.h \
    src/ui/colorpickform.h \
    src/ui/registerdialog.h \
    src/model/sqliteoperate.h \
    src/ui/collapseviewitem_contact.h \
    src/model/data_pools.h \
    src/ui/chatform.h

FORMS    += mainwindow.ui \
    src/ui/loginform.ui \
    src/ui/mainform.ui \
    src/ui/collapseview.ui \
    src/ui/collapseviewitem.ui \
    src/ui/litteriem.ui \
    src/ui/colorpickform.ui \
    src/ui/registerdialog.ui \
    src/ui/collapseviewitem_contact.ui \
    src/ui/chatform.ui

RESOURCES += \
    rs/rs.qrc
