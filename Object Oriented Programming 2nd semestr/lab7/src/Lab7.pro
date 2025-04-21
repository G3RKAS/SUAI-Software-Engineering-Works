QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apartemntcalcfactory.cpp \
    apartmentcalc.cpp \
    bstractcalc.cpp \
    calcfactory.cpp \
    calculationfacade.cpp \
    cottageapartemntcalcfactory.cpp \
    cottagecalc.cpp \
    estate.cpp \
    luxapartemntcalcfactory.cpp \
    luxuriousapartmentcalc.cpp \
    main.cpp \
    states.cpp \
    townhouseapartemntcalcfactory.cpp \
    townhousecalc.cpp \
    widget.cpp

HEADERS += \
    apartemntcalcfactory.h \
    apartmentcalc.h \
    bstractcalc.h \
    calcfactory.h \
    calculationfacade.h \
    cottageapartemntcalcfactory.h \
    cottagecalc.h \
    estate.h \
    luxapartemntcalcfactory.h \
    luxuriousapartmentcalc.h \
    states.h \
    townhouseapartemntcalcfactory.h \
    townhousecalc.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    facade.qmodel \
    factory.qmodel \
    observer.qmodel
