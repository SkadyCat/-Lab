#-------------------------------------------------
#
# Project created by QtCreator 2020-08-20T06:24:36
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDemo1013
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
        mainwindow.cpp \
    bluetooth.cpp \
    bme280.cpp \
    calculator.cpp \
    camera.cpp \
    decodingcubecontroller.cpp \
    dtcontroller.cpp \
    fileviewwidget.cpp \
    interrupt.cpp \
    led.cpp \
    mp3.cpp \
    pcf.cpp \
    processer.cpp \
    reader.cpp \
    superaudible.cpp \
    sx.cpp \
    task2window.cpp \
    threadsir.cpp \
    tool.cpp \
    writetool.cpp \
    gamewindow.cpp\
    resources.cpp

HEADERS += \
        mainwindow.h \
    bluetooth.h \
    bme280.h \
    calculator.h \
    camera.h \
    decodingcubecontroller.h \
    dtcontroller.h \
    fileviewwidget.h \
    interrupt.h \
    led.h \
    mainwindow.h \
    mp3.h \
    pcf.h \
    processer.h \
    reader.h \
    superaudible.h \
    sx.h \
    task2window.h \
    threadsir.h \
    tool.h \
    writetool.h \
    gamewindow.h\
    resources.h

FORMS += \
        mainwindow.ui \
    calculator.ui \
    m2.ui \
    mp3.ui \
    gamewindow.ui
unix {
    message("the prepalteform is liux or unix")
    HEADERS +=camerase.h
    HEADERS +=facesir.h
    HEADERS +=opencvtool.h

    SOURCES+=camerase.cpp
    SOURCES+=facesir.cpp
    SOURCES+=opencvtool.cpp

    LIBS += -lwiringPi
    INCLUDEPATH += .
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += /usr/local/include/opencv
    INCLUDEPATH += /usr/local/include/opencv2
    LIBS += `pkg-config opencv --cflags --libs`

}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    QDemo1013.pro

RESOURCES += \
    qss.qrc \
    res.qrc

DISTFILES += \
    Demo0003.pro.user \
    QDemo1013.pro.user \
    console.qss \
    demo.qss \
    menu.qss \
    menu2.qss
