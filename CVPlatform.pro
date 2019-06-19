#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T12:09:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CVPlatform
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

ICON =Icon.icns

SOURCES += main.cpp\
    Binaryzation.cpp \
    Correction.cpp \
    FindContours.cpp \
    ImageEnhancement.cpp \
    ImageMorphology.cpp \
    ImageOperation.cpp \
    ImageOperator.cpp \
    ImageSmoothing.cpp \
        mainwindow.cpp \
    processmodule.cpp \
    q2.cpp \
    roi.cpp

HEADERS  += mainwindow.h \
    Binaryzation.h \
    Correction.h \
    FindContours.h \
    ImageEnhancement.h \
    ImageMorphology.h \
    ImageOperation.h \
    ImageOperator.h \
    ImageSmoothing.h \
    MainHeader.h \
    ProHeader.h \
    processmodule.h \
    q2.h \
    roi.h \
    stdc++.h

FORMS    += mainwindow.ui

#INCLUDEPATH += T:/opencv/build/include
#INCLUDEPATH += /usr/local/Cellar/opencv/4.1.0_1/include/opencv4
#INCLUDEPATH += /usr/local/Cellar/opencv/4.1.0_1/include/opencv4/opencv2
INCLUDEPATH += E:\OpenCV-MinGW-Build-OpenCV-3.4.1\include
INCLUDEPATH += E:\OpenCV-MinGW-Build-OpenCV-3.4.1\include\opencv
INCLUDEPATH += E:\OpenCV-MinGW-Build-OpenCV-3.4.1\include\opencv2
#win32:CONFIG(debug, debug|release): {
#LIBS += -LT:/opencv/build/x86/vc12/lib \
#-lopencv_core2410d \
#-lopencv_imgproc2410d \
#-lopencv_highgui2410d \
#-lopencv_ml2410d \
#-lopencv_video2410d \
#-lopencv_features2d2410d \
#-lopencv_calib3d2410d \
#-lopencv_objdetect2410d \
#-lopencv_contrib2410d \
#-lopencv_legacy2410d \
#-lopencv_flann2410d

#} else:win32:CONFIG(release, debug|release): {
#LIBS += -LT:/opencv/build/x86/vc12/lib \
#-lopencv_core2410 \
#-lopencv_imgproc2410 \
#-lopencv_highgui2410 \
#-lopencv_ml2410 \
#-lopencv_video2410 \
#-lopencv_features2d2410 \
#-lopencv_calib3d2410 \
#-lopencv_objdetect2410 \
#-lopencv_contrib2410 \
#-lopencv_legacy2410 \
#-lopencv_flann2410 \
#-lopencv_nonfree2410
#}
#LIBS += /usr/local/Cellar/opencv/4.1.0_1/lib/lib*
LIBS +=E:\OpenCV-MinGW-Build-OpenCV-3.4.1\bin\lib*
DISTFILES += \
    Code.txt \
    Screen.JPG

RESOURCES += \
    resources.qrc
