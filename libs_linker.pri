#Where the DLLs are stored
DLL_FOLDER = $$_PRO_FILE_PWD_/../../../ext_lib/bin


#If we're building with Windows
win32:CONFIG(release, debug|release){

    #On release mode add the library object built from the image-duplicate-finder-lib project
    RELEASE_PATH = $$OUT_PWD/../image-duplicate-finder-lib/release/
LIBS += -L$$RELEASE_PATH -limage-duplicate-finder-lib

dll_install.files = $$DLL_FOLDER/opencv_core2413.dll $$DLL_FOLDER/opencv_highgui2413.dll \
$$DLL_FOLDER/opencv_features2d2413.dll $$DLL_FOLDER/opencv_nonfree2413.dll $$DLL_FOLDER/opencv_flann2413.dll \
$$DLL_FOLDER/opencv_imgproc2413.dll \
$$DLL_FOLDER/opencv_ocl2413.dll \
$$DLL_FOLDER/opencv_objdetect2413.dll \
$$DLL_FOLDER/opencv_ml2413.dll

    #Add the path to the release folder where the DLLs will be copied
    dll_install.path = $$OUT_PWD/release
}

else:win32:CONFIG(debug, debug|release){
    #On debug mode add the library built from the image-duplicate-finder-lib project
    DEBUG_PATH = $$OUT_PWD/../image-duplicate-finder-lib/debug/
    LIBS += -L$$DEBUG_PATH -limage-duplicate-finder-lib

dll_install.files = $$DLL_FOLDER/opencv_core2413d.dll $$DLL_FOLDER/opencv_highgui2413d.dll \
$$DLL_FOLDER/opencv_features2d2413d.dll $$DLL_FOLDER/opencv_nonfree2413d.dll $$DLL_FOLDER/opencv_flann2413d.dll \
$$DLL_FOLDER/opencv_imgproc2413d.dll \
$$DLL_FOLDER/opencv_ocl2413d.dll \
$$DLL_FOLDER/opencv_objdetect2413d.dll \
$$DLL_FOLDER/opencv_ml2413d.dll

    #Add the path to the debug folder where the DLLs will be copied
    dll_install.path = $$OUT_PWD/debug
}

unix|win32 {
CONFIG(debug, debug|release){
message(debug linked)

LIBS += -L$$_PRO_FILE_PWD_/../../../ext_lib/ -lopencv_core2413d \
-lopencv_highgui2413d \
-lopencv_features2d2413d \
-lopencv_nonfree2413d \
-lopencv_flann2413d \
-lopencv_imgproc2413d \
-lopencv_ocl2413d \
-lopencv_objdetect2413d \
-lopencv_ml2413d
}
else
{
LIBS += -L$$_PRO_FILE_PWD_/../../../ext_lib/ -lopencv_core2413 \
-lopencv_highgui2413 \
-lopencv_features2d2413 \
-lopencv_nonfree2413 \
-lopencv_flann2413 \
-lopencv_imgproc2413 \
-lopencv_ocl2413 \
-lopencv_objdetect2413 \
-lopencv_ml2413
}
}
#Install the DLLs
INSTALLS += dll_install
