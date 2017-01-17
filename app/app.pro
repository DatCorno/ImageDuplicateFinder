QT  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

SOURCES += .\src\main.cpp\
        .\src\mainwindow.cpp \

HEADERS  += .\include\mainwindow.h

FORMS    += .\ui\mainwindow.ui


INCLUDEPATH += $$PWD/../image-duplicate-finder-lib/include
INCLUDEPATH += $$PWD/../../../ext_lib/include
DEPENDPATH += $$PWD/../../../ext_lib/include

# Adds the QtQuickSampleLib.lib to the linker
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../image-duplicate-finder-lib/release/ -limage-duplicate-finder-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../image-duplicate-finder-lib/debug/ -limage-duplicate-finder-lib

unix|win32: LIBS += -L$$PWD/../../../ext_lib/ -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_features2d2413 \
    -lopencv_nonfree2413
