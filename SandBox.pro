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
HEADERS += src/core/Constants.h \
    src/viewer_3d/inc/IViewer3D.h \
    src/viewer_3d/inc/IViewer3DViewModel.h

# -----------------
# Extracted Feature: DICOM I/O
# -----------------
HEADERS += src/dicom/DicomLoader.h
SOURCES += src/dicom/DicomLoader.cpp

# -----------------
# Extracted Feature: 3D Viewer
# -----------------

HEADERS += \
    src/viewer_3d/inc/IModel.h \
    src/viewer_3d/inc/Types.h \
    src/viewer_3d/inc/m3d_factory.h \

HEADERS += \
    src/viewer_3d/src/VolumePipeline.h \
    src/viewer_3d/src/Viewer3DViewModel.h \
    src/viewer_3d/src/Viewer3DWidget.h

SOURCES += \
    src/viewer_3d/src/VolumePipeline.cpp \
    src/viewer_3d/src/Viewer3DViewModel.cpp \
    src/viewer_3d/src/Viewer3DWidget.cpp \
    src/viewer_3d/src/m3d_factory.cpp

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


RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    todo.txt
