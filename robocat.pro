#-------------------------------------------------
#
# Project created by QtCreator 2019-04-05T00:35:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robocat
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
    connectdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    chronolabel.cpp \
    robodatabase.cpp \
    sentenciessql.cpp \
    scalingimage.cpp \
    equipdialog.cpp \
    partidadialog.cpp \
    pantallapuntuacio.cpp \
    pantallacrono.cpp

HEADERS += \
    connectdialog.h \
    mainwindow.h \
    chronolabel.h \
    robodatabase.h \
    data_objects/connectioninfo.h \
    sentenciessql.h \
    scalingimage.h \
    constants.h \
    equipdialog.h \
    partidadialog.h \
    data_objects/partida.h \
    pantallapuntuacio.h \
    data_objects/equip.h \
    pantallacrono.h

FORMS += \
        mainwindow.ui \
    connectdialog.ui \
    pantalles_crono/cronoidle.ui \
    pantalles_crono/cronoseguents.ui \
    pantalles_crono/cronoplaying.ui \
    equipdialog.ui \
    partidadialog.ui \
    pantallapuntuacio.ui

RESOURCES += \
    resources.qrc \
    sql/sql.qrc

DISTFILES += \
    README.md
