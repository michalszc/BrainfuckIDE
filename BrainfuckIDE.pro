QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = BrainfuckIDE
TEMPLATE = app
SUBDIRS += ui
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
INCLUDEPATH += src

SOURCES += \
    src/Controller.cpp \
    src/Interpreter.cpp \
    src/codeeditor.cpp \
    src/highlighter.cpp \
    src/linenumberarea.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settings.cpp

HEADERS += \
    src/BeginLoop.h \
    src/Brainfuck.h \
    src/Controller.h \
    src/EndLoop.h \
    src/Input.h \
    src/Instruction.h \
    src/Interpreter.h \
    src/Memory.h \
    src/Minus.h \
    src/MoveLeft.h \
    src/MoveRight.h \
    src/Output.h \
    src/Plus.h \
    src/RangeError.h \
    src/codeeditor.h \
    src/highlighter.h \
    src/linenumberarea.h \
    src/mainwindow.h \
    src/settings.h

FORMS += \
    ui/mainwindow.ui \
    ui/settings.ui

RESOURCES += \
    Examples.qrc

include(QtAwesome/QtAwesome.pri)
