#pragma once

#include <QMainWindow>
#include <QSlider>
// #include "MainViewModel.h"

// #include "src/viewer_3d/inc/.h"
// #include "viewer_3d/viewer3dwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // explicit MainWindow(MainViewModel *viewModel, QWidget *parent = nullptr);
    explicit MainWindow(QWidget *parent = nullptr);

private:
    // void setupPalette();
    void setupUI();
    void setupViews();
    // MainViewModel *m_viewModel;
    // Viewer3DViewModel *m_viewer3DViewModel;
    // Viewer3DWidget *m_viewer3DWidget;

    QSlider *m_slider = nullptr;
};
