TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    fsm.c \
    display.c \
    keyboard.c \
    coolDown.c \
    error.c \
    optionsMenu.c \
    safety.c \
    testSequence.c

HEADERS += \
    keyboard.h \
    fsm.h \
    events.h \
    display.h \
    optionMenu.h \
    safety.h \
    error.h \
    coolDown.h \
    testSequence.h
