#pragma once

#include <QMainWindow>
#include "mainviewmodel.h"
#include "viewer_3d/viewer3dwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(MainViewModel *viewModel, QWidget *parent = nullptr);

private:
    MainViewModel *m_viewModel;
    Viewer3DWidget *m_viewer3DWidget;

    void setupUI();
};
