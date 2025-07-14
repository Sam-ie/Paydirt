QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    antique.cpp \
    futures.cpp \
    help.cpp \
    lottery.cpp \
    main.cpp \
    entrance.cpp \
    mainwindow.cpp \
    player.cpp \
    select_difficulty.cpp

HEADERS += \
    antique.h \
    entrance.h \
    futures.h \
    help.h \
    lottery.h \
    mainwindow.h \
    player.h \
    select_difficulty.h

FORMS += \
    antique.ui \
    entrance.ui \
    futures.ui \
    help.ui \
    lottery.ui \
    mainwindow.ui \
    select_difficulty.ui

TRANSLATIONS += \
    Paydirt_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res_Paydirt.qrc

DISTFILES +=

RC_ICONS = res/RIcon1.ico
