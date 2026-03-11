#pragma once

#include <QMainWindow>
#include <QSlider>
#include <QVTKOpenGLNativeWidget.h>
#include "MainViewModel.h"
#include "src/viewer_3d/inc/IViewer3D.h"

// #include "src/viewer_3d/inc/.h"
// #include "viewer_3d/viewer3dwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // explicit MainWindow(MainViewModel *viewModel, QWidget *parent = nullptr);
    explicit MainWindow(std::shared_ptr<MainViewModel> mainVM,
                        Viewer3D::Interfaces::IViewer3D *main3D,
                        Viewer3D::Interfaces::IViewer3D *sagittal,
                        Viewer3D::Interfaces::IViewer3D *coronal,
                        Viewer3D::Interfaces::IViewer3D *axial,
                        QWidget *parent = nullptr);
signals:
    void blendModeChanged(Viewer3D::BlendMode mode);

private:
    void setupUI();
    void setupViews();

    std::shared_ptr<MainViewModel> m_mainVM;
    Viewer3D::Interfaces::IViewer3D *m_main3D = nullptr;
    Viewer3D::Interfaces::IViewer3D *m_sagittal = nullptr;
    Viewer3D::Interfaces::IViewer3D *m_coronal = nullptr;
    Viewer3D::Interfaces::IViewer3D *m_axial = nullptr;

    QWidget *coronal = nullptr;
    QWidget *axial = nullptr;
    QWidget *sagittal = nullptr;

    QSlider *m_slider = nullptr;
};
