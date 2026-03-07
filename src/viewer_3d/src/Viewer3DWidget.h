#pragma once

#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include "src/viewer_3d/inc/IModel.h"
#include "src/viewer_3d/inc/IViewer3D.h"
#include "viewer3dviewmodel.h"
#include "vtkCamera.h"

class Viewer3DWidget : public QWidget, public Viewer3D::Interfaces::IViewer3D
{
    Q_OBJECT
public:
    explicit Viewer3DWidget(std::shared_ptr<Viewer3DViewModel> viewModel, QWidget *parent = nullptr);
    ~Viewer3DWidget() override = default;
    void setBlendMode(BlendMode mode);
private slots:
    void onDataPropsReady();

    [[nodiscard]] QWidget *asWidget() override { return this; };

private:
    std::shared_ptr<Viewer3DViewModel> m_viewModel;
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_mapper;
    vtkSmartPointer<vtkVolume> m_volume;
    QVTKOpenGLNativeWidget *m_vtkWidget;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkCamera> m_camera;

    void setupUI();
    void setupVtk();
};
