QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    clientsmenu.cpp \
    main.cpp \
    mainwindow.cpp \
    mastersmenu.cpp \
    order.cpp \
    ordermanipulate.cpp \
    ordersmenu.cpp \
    worker.cpp

HEADERS += \
    client.h \
    clientsmenu.h \
    mainwindow.h \
    mastersmenu.h \
    order.h \
    ordermanipulate.h \
    ordersmenu.h \
    worker.h

FORMS += \
    clientsmenu.ui \
    mainwindow.ui \
    mastersmenu.ui \
    ordersmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    application.qmodel \
    facade.qmodel \
    observer.qmodel
