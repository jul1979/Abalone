TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pedantic-errors

SOURCES += \
        controller.cpp \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../model/release/ -lmodel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../model/debug/ -lmodel
else:unix: LIBS += -L$$OUT_PWD/../model/ -lmodel

INCLUDEPATH += $$PWD/../model
DEPENDPATH += $$PWD/../model

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/release/libmodel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/debug/libmodel.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/release/model.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/debug/model.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../model/libmodel.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../view/release/ -lview
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../view/debug/ -lview
else:unix: LIBS += -L$$OUT_PWD/../view/ -lview

INCLUDEPATH += $$PWD/../view
DEPENDPATH += $$PWD/../view

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../view/release/libview.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../view/debug/libview.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../view/release/view.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../view/debug/view.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../view/libview.a

HEADERS += \
    controller.h
