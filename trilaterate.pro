QT += core widgets qml quick 3dcore testlib

CONFIG += c++11 qml_debug testcase

TARGET = trilaterate
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH += "$$PWD/../lib/"

SOURCES += main.cpp \
    trivector.cpp \
    demooutput.cpp \
    etc-osc/OSCMessage.cpp \
    etc-osc/OSCNetworkManager.cpp \
    etc-osc/OSCParser.cpp \
    trilaterate.cpp \
    tests/testtrilaterate.cpp

HEADERS += \
        demooutput.h \
        trivector.h \
        inputinterface.h \
# From ETC S2L.
        etc-osc/OSCMessage.h \
        etc-osc/OSCNetworkManager.h \
        etc-osc/OSCParser.h \
        etc-osc/utils.h \
    trilaterate.h

DISTFILES += \
    mainwindow.qml \
    PointInput.qml

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-trilaterate-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/release/ -ltrilaterate-lib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-trilaterate-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/ -ltrilaterate-lib
#else:unix: LIBS += -L$$PWD/../lib/ -ltrilaterate-lib.1.0.0

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

INCLUDEPATH += $$PWD/../build-trilaterate-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug
DEPENDPATH += $$PWD/../build-trilaterate-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug

RESOURCES += \
    trilaterate.qrc
