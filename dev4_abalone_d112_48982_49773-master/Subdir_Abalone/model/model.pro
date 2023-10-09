QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += console c++17
MAKE_CXXFLAGS += -pedantic-errors


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Square.cpp \
    board.cpp \
    game.cpp \
    hexagon.cpp \
    marble.cpp \
    observer/subject.cpp \
    player.cpp \
    position.cpp

HEADERS += \
    alphabet.h \
    board.h \
    color.h \
    direction.h \
    game.h \
    hexagon.h \
    marble.h \
    movetype.h \
    observer/observer.h \
    observer/subject.h \
    player.h \
    position.h \
    square.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
