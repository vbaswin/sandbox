#pragma once

#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include "src/viewer_3d/inc/IViewer3D.h"
#include "viewer3dviewmodel.h"
#include "vtkCamera.h"

class Viewer3DWidget : public QWidget, public Viewer3D::Interfaces::IViewer3D
{
    Q_OBJECT
public:
    explicit Viewer3DWidget(std::unique_ptr<Viewer3DViewModel> viewModel, QWidget *parent = nullptr);
    ~Viewer3DWidget() override = default;
private slots:
    void onVolumeReady();
    void reRender();

    [[nodiscard]] QWidget *asWidget() override { return this; };

private:
    std::unique_ptr<Viewer3DViewModel> m_viewModel;
    QVTKOpenGLNativeWidget *m_vtkWidget;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkCamera> m_camera;

    void setupUI();
    void setupVtk();
};
