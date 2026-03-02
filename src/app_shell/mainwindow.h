#pragma once

#include <QMainWindow>
#include <QSlider>

#include "mainviewmodel.h"
#include "viewer_3d/viewer3dwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(MainViewModel *viewModel, QWidget *parent = nullptr);

private:
    MainViewModel *m_viewModel;
    Viewer3DViewModel *m_viewer3DViewModel;
    Viewer3DWidget *m_viewer3DWidget;

    QSlider *m_slider = nullptr;
    void setupUI();
};
