TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core gui
QT += testlib
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

FORMS += \
    Ui/mainwindow.ui \
    Ui/startscreen.ui

SOURCES += \
        Ui/abstractui.cpp \
        Tiles/active.cpp \
        Controller/attackcontroller.cpp \
        Other/character.cpp \
        Controller/controller.cpp \
        Tiles/door.cpp \
        Other/dungeoncrawler.cpp \
        Tiles/floor.cpp \
        Ui/graphicalui.cpp \
        Controller/guardcontroller.cpp \
        Other/level.cpp \
        Tiles/levelchanger.cpp \
        Other/list.cpp \
        Tiles/lootchest.cpp \
        main.cpp \
        Ui/mainwindow.cpp \
        Tiles/passive.cpp \
        Tiles/pit.cpp \
        Tiles/portal.cpp \
        Tiles/ramp.cpp \
        Ui/startscreen.cpp \
        Controller/stationarycontroller.cpp \
        Tiles/switch.cpp \
        Ui/terminalui.cpp \
        Tiles/tile.cpp \
        Tiles/wall.cpp

HEADERS += \
    Ui/abstractui.h \
    Tiles/active.h \
    Controller/attackcontroller.h \
    Other/character.h \
    Controller/controller.h \
    Tiles/door.h \
    Other/dungeoncrawler.h \
    Tiles/floor.h \
    Ui/graphicalui.h \
    Controller/guardcontroller.h \
    Other/level.h \
    Tiles/levelchanger.h \
    Other/list.h \
    Tiles/lootchest.h \
    Ui/mainwindow.h \
    Tiles/passive.h \
    Tiles/pit.h \
    Tiles/portal.h \
    Tiles/ramp.h \
    Ui/startscreen.h \
    Controller/stationarycontroller.h \
    Tiles/switch.h \
    Ui/terminalui.h \
    Tiles/tile.h \
    Tiles/wall.h

RESOURCES += \
    Resources.qrc
