#pragma once

#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include "viewer3dviewmodel.h"
#include "vtkCamera.h"

class Viewer3DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer3DWidget(Viewer3DViewModel *viewModel, QWidget *parent = nullptr);
    ~Viewer3DWidget() override = default;
private slots:
    void onVolumeReady();

private:
    Viewer3DViewModel *m_viewModel;
    QVTKOpenGLNativeWidget *m_vtkWidget;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkCamera> m_camera;

    void setupUI();
    void setupVtk();
};
