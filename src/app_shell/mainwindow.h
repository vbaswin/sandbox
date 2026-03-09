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
                        std::shared_ptr<Viewer3D::Interfaces::IViewer3D> viewer,
                        QWidget *parent = nullptr);

private:
    void setupUI();
    void setupViews();

    std::shared_ptr<Viewer3D::Interfaces::IViewer3D> m_viewer3D;
    std::shared_ptr<MainViewModel> m_mainVM;

    QWidget *coronal = nullptr;
    QWidget *axial = nullptr;
    QWidget *sagittal = nullptr;

    QSlider *m_slider = nullptr;
};
