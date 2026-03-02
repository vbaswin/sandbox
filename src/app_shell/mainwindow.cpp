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
    m_viewer3DViewModel = m_viewModel->getViewer3DViewModel();
    setupUI();
    QObject::connect(m_slider,
                     &QSlider::valueChanged,
                     m_viewer3DViewModel,
                     &Viewer3DViewModel::setRangeStart);
}

void MainWindow::setupUI()
{
    QWidget *mainWidget = new QWidget(this);

    this->setCentralWidget(mainWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);

    m_viewer3DWidget = new Viewer3DWidget(m_viewer3DViewModel);
    mainLayout->addWidget(m_viewer3DWidget, 1);

    QWidget *rightControlPanel = new QWidget(mainWidget);
    QVBoxLayout *controlsLayout = new QVBoxLayout(rightControlPanel);

    mainLayout->addWidget(rightControlPanel);

    QLabel *windowLabel = new QLabel("Window size", rightControlPanel);
    m_slider = new QSlider(Qt::Vertical, rightControlPanel);
    // m_slider->setMinimum(0);
    m_slider->setMinimum(-1000);
    m_slider->setMaximum(100);
    controlsLayout->addWidget(windowLabel);
    controlsLayout->addWidget(m_slider);
    // m_slider->setMinimumWidth(150);
    m_slider->setMinimumHeight(700);
    m_slider->setValue(100);
    controlsLayout->addStretch();
}
