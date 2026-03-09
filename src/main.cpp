#include <QDebug>
#include <QFile>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>
#include "QVTKOpenGLWidget.h"
#include "app_shell/mainWindow.h"
#include "app_shell/mainviewmodel.h"
#include "core/Contants.h"
#include "src/viewer_3d/inc/IViewer3D.h"
#include "src/viewer_3d/inc/Types.h"
#include "src/viewer_3d/src/Viewer3DWidget.h"
#include "src/viewer_3d/src/VolumePipeline.h"
#include <iostream>
#include <qapplication.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

int main(int argc, char *argv[])
{
    qRegisterMetaType<Viewer3D::BlendMode>("BlendMode");

    // Essential for vtkGPUVolumeRayCastMapper when using QVTKOpenGLNativeWidget:
    // 1. Disable Multi-Sampling (MSAA) which interferes with VTK's offscreen volume rendering passes.
    QSurfaceFormat format = QVTKOpenGLNativeWidget::defaultFormat();
    format.setSamples(0);
    QSurfaceFormat::setDefaultFormat(format);

    // 2. Share OpenGL contexts across the application to ensure VTK shaders and textures load properly.
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication app(argc, argv);
    QFile styleFile(":/styles/modern_dark.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qWarning() << "Failed to load stylesheet!";
    }

    // std::unique_ptr<Viewer3D::Interfaces::IViewer3DViewModel>
    std::shared_ptr<VolumePipeline> volPipeline = std::make_shared<VolumePipeline>();
    std::shared_ptr<Viewer3DViewModel> viewer3DVM = std::make_shared<Viewer3DViewModel>(volPipeline);

    std::shared_ptr<MainViewModel> mainVM = std::make_shared<MainViewModel>(viewer3DVM);

    auto main3D = new Viewer3DWidget(viewer3DVM, Viewer3D::viewOrientation::Main3D);
    auto coronal = new Viewer3DWidget(viewer3DVM, Viewer3D::viewOrientation::Sagittal);
    auto axial = new Viewer3DWidget(viewer3DVM, Viewer3D::viewOrientation::Axial);
    auto sagittal = new Viewer3DWidget(viewer3DVM, Viewer3D::viewOrientation::Coronal);

    // std::shared_ptr<Viewer3DWidget> viewer3DWidget = std::make_shared<Viewer3DWidget>(viewer3DVM);

    MainWindow w(mainVM, main3D, sagittal, coronal, axial);

    w.show();
    mainVM->executeInitialAppLoad(Constants::DEFAULT_DICOM_DIR);
    // viewModel.executeInitialAppLoad(Constants::DEFAULT_DICOM_DIR);

    return app.exec();
}
