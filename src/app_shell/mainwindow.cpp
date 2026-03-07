#include "mainwindow.h"
#include <QAction>
#include <QActionGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QSlider>
#include <QSplitter>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVTKOpenGLNativeWidget.h>
#include "src/viewer_3d/inc/IViewer3D.h"

// MainWindow::MainWindow(MainViewModel *viewModel, QWidget *parent)
//     : QMainWindow(parent)
//     , m_viewModel(viewModel)
MainWindow::MainWindow(std::unique_ptr<Viewer3D::Interfaces::IViewer3D> viewer3D, QWidget *parent)
    : m_viewer3D(std::move(viewer3D))
{
    this->resize(1920, 1080);
    // m_viewer3DViewModel = m_viewModel->getViewer3DViewModel();
    setupUI();
    setupViews();
    // QObject::connect(m_slider,
    //                  &QSlider::valueChanged,
    //                  m_viewer3DViewModel,
    // &Viewer3DViewModel::setRangeStart);
}

void MainWindow::setupUI()
{
    // QStackedWidget *stackedWidget = new QStackedWidget(this);

    // QWidget *MPR = new QWidget(stackedWidget);
    // QWidget *RS = new QWidget(stackedWidget); // Range shift

    // stackedWidget->addWidget(MPR);
    // stackedWidget->addWidget(RS);

    // QVBoxLayout *layout = new QVBoxLayout;
    // layout->addWidget(stackedWidget);
    // setLayout(layout);

    QToolBar *toolbar = new QToolBar(this);
    this->addToolBar(toolbar);

    // QButtonGroup *funcGroup = new QButtonGroup(this);
    // QPushButton *DRR = new QPushButton(this);
    // QPushButton *MIP = new QPushButton(this);
    // QPushButton *RS = new QPushButton(this);

    // DRR->setCheckable(true);
    // MIP->setCheckable(true);
    // RS->setCheckable(true);

    // funcGroup->addButton(DRR);
    // funcGroup->addButton(MIP);
    // funcGroup->addButton(RS);

    // funcGroup->setExclusive(true);

    QActionGroup *modeGroup = new QActionGroup(this);
    modeGroup->setExclusive(true);

    QAction *actDRR = toolbar->addAction("DRR");
    actDRR->setCheckable(true);
    modeGroup->addAction(actDRR);

    QAction *actMIP = toolbar->addAction("MIP");
    actMIP->setCheckable(true);
    modeGroup->addAction(actMIP);

    QAction *actRS = toolbar->addAction("RS");
    actRS->setCheckable(true);
    modeGroup->addAction(actRS);

    // toolbar->add
}

void MainWindow::setupViews()
{
    QSplitter *verSplitter1 = new QSplitter(Qt::Vertical, this);
    QSplitter *verSplitter2 = new QSplitter(Qt::Vertical, this);
    QSplitter *horSplitter = new QSplitter(Qt::Horizontal, this);

    horSplitter->addWidget(verSplitter1);
    horSplitter->addWidget(verSplitter2);

    // threeD = new QVTKOpenGLNativeWidget(this);
    axial = new QVTKOpenGLNativeWidget(this);
    coronal = new QVTKOpenGLNativeWidget(this);
    sagittal = new QVTKOpenGLNativeWidget(this);

    verSplitter1->addWidget(m_viewer3D->asWidget());
    verSplitter1->addWidget(coronal);

    verSplitter2->addWidget(sagittal);
    verSplitter2->addWidget(axial);
    this->setCentralWidget(horSplitter);

    // m_viewer3D->setMinimumSize(100, 100);
    axial->setMinimumSize(100, 100);
    coronal->setMinimumSize(100, 100);
    sagittal->setMinimumSize(100, 100);

    // threeD->setObjectName("medicalSlice");
    axial->setObjectName("medicalSlice");
    sagittal->setObjectName("medicalSlice");
    coronal->setObjectName("medicalSlice");

    connect(verSplitter2, &QSplitter::splitterMoved, [=]() {
        verSplitter1->setSizes(verSplitter2->sizes());
    });
    connect(verSplitter1, &QSplitter::splitterMoved, [=]() {
        verSplitter2->setSizes(verSplitter1->sizes());
    });
}

// with slider
// void MainWindow::setupUI()
// {
//     QWidget *mainWidget = new QWidget(this);

//     this->setCentralWidget(mainWidget);
//     QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);

//     m_viewer3DWidget = new Viewer3DWidget(m_viewer3DViewModel);
//     mainLayout->addWidget(m_viewer3DWidget, 1);

//     QWidget *rightControlPanel = new QWidget(mainWidget);
//     QVBoxLayout *controlsLayout = new QVBoxLayout(rightControlPanel);

//     mainLayout->addWidget(rightControlPanel);

//     QLabel *windowLabel = new QLabel("Window size", rightControlPanel);
//     m_slider = new QSlider(Qt::Vertical, rightControlPanel);
//     // m_slider->setMinimum(0);
//     m_slider->setMinimum(-1000);
//     m_slider->setMaximum(100);
//     controlsLayout->addWidget(windowLabel);
//     controlsLayout->addWidget(m_slider);
//     // m_slider->setMinimumWidth(150);
//     m_slider->setMinimumHeight(700);
//     m_slider->setValue(100);
//     controlsLayout->addStretch();
// }
