#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QSlider>
#include <QVBoxLayout>

MainWindow::MainWindow(MainViewModel *viewModel, QWidget *parent)
    : QMainWindow(parent)
    , m_viewModel(viewModel)
{
    this->resize(1920, 1080);
    setupUI();
}

void MainWindow::setupUI()
{
    QWidget *mainWidget = new QWidget(this);

    this->setCentralWidget(mainWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);

    m_viewer3DWidget = new Viewer3DWidget(m_viewModel->getViewer3DViewModel(), this);
    mainLayout->addWidget(m_viewer3DWidget, 1);

    QWidget *rightControlPanel = new QWidget(mainWidget);
    QVBoxLayout *controlsLayout = new QVBoxLayout(rightControlPanel);

    mainLayout->addWidget(rightControlPanel);

    QLabel *windowLabel = new QLabel("Window size", rightControlPanel);
    QSlider *slider = new QSlider(Qt::Horizontal, rightControlPanel);
    controlsLayout->addWidget(windowLabel);
    controlsLayout->addWidget(slider);
    slider->setMinimumWidth(150);
    controlsLayout->addStretch();
}
