TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core gui
QT += testlib
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

FORMS += \
    mainwindow.ui \
    startscreen.ui

SOURCES += \
        abstractui.cpp \
        active.cpp \
        attackcontroller.cpp \
        character.cpp \
        controller.cpp \
        door.cpp \
        dungeoncrawler.cpp \
        floor.cpp \
        graphicalui.cpp \
        guardcontroller.cpp \
        level.cpp \
        levelchanger.cpp \
        list.cpp \
        lootchest.cpp \
        main.cpp \
        mainwindow.cpp \
        passive.cpp \
        pit.cpp \
        portal.cpp \
        ramp.cpp \
        startscreen.cpp \
        stationarycontroller.cpp \
        switch.cpp \
        terminalui.cpp \
        tile.cpp \
        wall.cpp

HEADERS += \
    abstractui.h \
    active.h \
    attackcontroller.h \
    character.h \
    controller.h \
    door.h \
    dungeoncrawler.h \
    floor.h \
    graphicalui.h \
    guardcontroller.h \
    level.h \
    levelchanger.h \
    list.h \
    lootchest.h \
    mainwindow.h \
    passive.h \
    pit.h \
    portal.h \
    ramp.h \
    startscreen.h \
    stationarycontroller.h \
    switch.h \
    terminalui.h \
    tile.h \
    wall.h

RESOURCES += \
    Resources.qrc
