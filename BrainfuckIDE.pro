QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller.cpp \
    Interpreter.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    linenumberarea.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BeginLoop.h \
    Brainfuck.h \
    Controller.h \
    EndLoop.h \
    Input.h \
    Instruction.h \
    Interpreter.h \
    Memory.h \
    Minus.h \
    MoveLeft.h \
    MoveRight.h \
    Output.h \
    Plus.h \
    RangeError.h \
    codeeditor.h \
    highlighter.h \
    linenumberarea.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Examples.qrc
