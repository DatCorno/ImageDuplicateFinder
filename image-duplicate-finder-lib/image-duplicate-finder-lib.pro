#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T17:10:29
#
#-------------------------------------------------

QT       -= gui

TARGET = image-duplicate-finder-lib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

SOURCES += \
    src/directoryexplorer.cpp \
    src/duplicatefinder.cpp

HEADERS += \
        include/duplicatefinder.h \
    include/directoryexplorer.h \
    include/imagetype.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../../../ext_lib/include
DEPENDPATH += $$PWD/../../../ext_lib/include

#Add the .lib object for unix systems and Windows

unix|win32 {
CONFIG(debug, debug|release){
message(debug linked)

LIBS += -L$$_PRO_FILE_PWD_/../../../ext_lib/ -lopencv_core2413d \
-lopencv_highgui2413d \
-lopencv_features2d2413d \
-lopencv_nonfree2413d \
-opencv_flann2413d \
-lopencv_imgproc2413 \
-lopencv_ocl2413 \
-lopencv_objdetect2413 \
-lopencv_ml2413
}
else
{
LIBS += -L$$_PRO_FILE_PWD_/../../../ext_lib/ -lopencv_core2413 \
-lopencv_highgui2413 \
-lopencv_features2d2413 \
-lopencv_nonfree2413 \
-lopencv_flann2413
}
}
