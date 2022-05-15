TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractui.cpp \
        active.cpp \
        character.cpp \
        door.cpp \
        dungeoncrawler.cpp \
        floor.cpp \
        level.cpp \
        main.cpp \
        passive.cpp \
        portal.cpp \
        switch.cpp \
        terminalui.cpp \
        tile.cpp \
        wall.cpp

HEADERS += \
    abstractui.h \
    active.h \
    character.h \
    door.h \
    dungeoncrawler.h \
    floor.h \
    level.h \
    passive.h \
    portal.h \
    switch.h \
    terminalui.h \
    tile.h \
    wall.h
