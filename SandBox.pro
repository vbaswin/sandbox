QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sandbox
TEMPLATE = app

include(./shared_config.pri)

# Let qmake find headers like #include "dicom/DicomLoader.h"
INCLUDEPATH += $$PWD/src

# -----------------
# Core Infrastructure
# -----------------
HEADERS += src/core/Constants.h

# -----------------
# Extracted Feature: DICOM I/O
# -----------------
HEADERS += src/dicom/DicomLoader.h
SOURCES += src/dicom/DicomLoader.cpp

# -----------------
# Extracted Feature: 3D Viewer
# -----------------
HEADERS += \
    src/viewer_3d/VolumePipeline.h \
    src/viewer_3d/Viewer3DViewModel.h \
    src/viewer_3d/Viewer3DWidget.h

SOURCES += \
    src/viewer_3d/VolumePipeline.cpp \
    src/viewer_3d/Viewer3DViewModel.cpp \
    src/viewer_3d/Viewer3DWidget.cpp

# -----------------
# Extracted Feature: App Shell (Window & Integration)
# -----------------
HEADERS += \
    src/app_shell/MainViewModel.h \
    src/app_shell/MainWindow.h

SOURCES += \
    src/main.cpp \
    src/app_shell/MainViewModel.cpp \
    src/app_shell/MainWindow.cpp
