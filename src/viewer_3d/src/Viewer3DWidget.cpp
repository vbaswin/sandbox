#include "viewer3dwidget.h"
#include <QVBoxLayout>
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkRenderer.h"

Viewer3DWidget::Viewer3DWidget(std::shared_ptr<Viewer3DViewModel> viewModel, QWidget *parent)
    : QWidget(parent)
    , m_viewModel(viewModel)
{
    setupUI();
    setupVtk();

    connect(m_viewModel.get(),
            &Viewer3DViewModel::volumeReady,
            this,
            &Viewer3DWidget::onVolumeReady);
    connect(m_viewModel.get(), &Viewer3DViewModel::reRender, this, &Viewer3DWidget::reRender);
}

void Viewer3DWidget::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_vtkWidget = new QVTKOpenGLNativeWidget(this);
    layout->addWidget(m_vtkWidget);
}

void Viewer3DWidget::setupVtk()
{
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    m_renderWindow->AddRenderer(m_renderer);
    m_renderWindow->SetWindowName("openglraycastmapper");

    m_vtkWidget->SetRenderWindow(m_renderWindow);
}
void Viewer3DWidget::reRender()
{
    m_renderWindow->Render();
}

void Viewer3DWidget::onVolumeReady()
{
    m_renderer->RemoveAllViewProps();
    m_renderer->AddVolume(m_viewModel->getVolume());
    m_renderer->ResetCameraClippingRange();
    m_renderer->ResetCamera();
    m_renderWindow->Render();
}
