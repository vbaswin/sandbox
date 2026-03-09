#include "viewer3dwidget.h"
#include <QVBoxLayout>
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkRenderer.h"

Viewer3DWidget::Viewer3DWidget(std::shared_ptr<Viewer3DViewModel> viewModel,
                               Viewer3D::viewOrientation orient,
                               QWidget *parent)
    : QWidget(parent)
    , m_viewModel(viewModel)
{
    setupUI();
    setupVtk();

    connect(m_viewModel.get(),
            &Viewer3DViewModel::dataPropertyReady,
            this,
            &Viewer3DWidget::onDataPropertyReady);
    connect(m_viewModel.get(),
            &Viewer3DViewModel::blendModeChanged,
            this,
            &Viewer3DWidget::onBlendModeChanged);
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
    m_mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    // m_mapper->AutoAdjustSampleDistancesOn();
    m_mapper->SetBlendModeToComposite();
    // m_mapper->SetBlendModeToMaximumIntensity();
    m_volume = vtkSmartPointer<vtkVolume>::New();
    m_volume->SetMapper(m_mapper);
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    m_renderWindow->AddRenderer(m_renderer);
    m_renderWindow->SetWindowName("openglraycastmapper");

    m_vtkWidget->SetRenderWindow(m_renderWindow);
}

void Viewer3DWidget::setBlendMode(Viewer3D::BlendMode mode)
{
    switch (mode) {
    case Viewer3D::BlendMode::Composite:
        m_mapper->SetBlendModeToComposite();
        break;
    case Viewer3D::BlendMode::Additive:
        m_mapper->SetBlendModeToAdditive();
        break;
    case Viewer3D::BlendMode::MaximumIntensity:
        m_mapper->SetBlendModeToMaximumIntensity();
        break;
    }
}
void Viewer3DWidget::onBlendModeChanged(Viewer3D::BlendMode mode)
{
    setBlendMode(mode);
}

void Viewer3DWidget::onDataPropertyReady()
{
    m_volume->SetProperty(m_viewModel->getVolumeProperty());
    m_mapper->SetInputData(m_viewModel->getImageData());
    // m_mapper->SetSampleDistance(0.000001);
    setBlendMode(Viewer3D::BlendMode::Composite);
    // setBlendMode(BlendMode::MaximumIntensity);
    // setBlendMode(BlendMode::Additive);
    m_renderer->RemoveAllViewProps();
    m_renderer->AddVolume(m_volume);
    m_renderer->ResetCameraClippingRange();
    m_renderer->ResetCamera();
    m_renderWindow->Render();
}
