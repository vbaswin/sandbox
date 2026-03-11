#include "src/viewer_3d/View/viewer3dwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include "src/viewer_3d/View/Interactions/ClippingPlaneInteractorStyle.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkPlane.h"
#include "vtkRenderer.h"

Viewer3DWidget::Viewer3DWidget(std::shared_ptr<Viewer3DViewModel> viewModel,
                               Viewer3D::viewOrientation orient,
                               QWidget *parent)
    : QWidget(parent)
    , m_viewModel(viewModel)
    , m_orient(orient)
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

    m_camera = m_renderer->GetActiveCamera();
    vtkSmartPointer<vtkPlane> clipPlane = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<Viewer3D::Interactions::ClippingPlaneInteractorStyle> customStyle
        = vtkSmartPointer<Viewer3D::Interactions::ClippingPlaneInteractorStyle>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> trackballStyle
        = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

    double stepSize = 2.0;
    switch (m_orient) {
    case Viewer3D::viewOrientation::Main3D:
        m_camera->SetParallelProjection(0);
        m_renderWindow->GetInteractor()->SetInteractorStyle(trackballStyle);
        break;
    case Viewer3D::viewOrientation::Axial:
        m_camera->SetPosition(0, 0, 1);
        m_camera->SetFocalPoint(0, 0, 0);
        // according to the dicom, y up because +y is anterior
        m_camera->SetViewUp(0, 1, 0);

        clipPlane->SetOrigin(0, 0, 0);
        // normal towards +z to ut away the foreground
        clipPlane->SetNormal(0, 0, 1);
        m_mapper->AddClippingPlane(clipPlane);
        m_camera->SetParallelProjection(1);
        customStyle->SetClippingPlane(clipPlane, 2, stepSize);
        m_renderWindow->GetInteractor()->SetInteractorStyle(customStyle);
        break;
    case Viewer3D::viewOrientation::Sagittal:
        m_camera->SetPosition(1, 0, 0);
        m_camera->SetFocalPoint(0, 0, 0);
        m_camera->SetViewUp(0, 0, 1);

        clipPlane->SetOrigin(0, 0, 0);
        clipPlane->SetNormal(1, 0, 0); // towards +x
        m_mapper->AddClippingPlane(clipPlane);
        m_camera->SetParallelProjection(1);
        customStyle->SetClippingPlane(clipPlane, 0, stepSize);
        m_renderWindow->GetInteractor()->SetInteractorStyle(customStyle);
        break;
    case Viewer3D::viewOrientation::Coronal:
        m_camera->SetPosition(0, 1, 0);
        m_camera->SetFocalPoint(0, 0, 0);
        m_camera->SetViewUp(0, 0, 1);

        clipPlane->SetOrigin(0, 0, 0);
        clipPlane->SetNormal(0, 1, 0);
        m_mapper->AddClippingPlane(clipPlane);
        m_camera->SetParallelProjection(1);
        customStyle->SetClippingPlane(clipPlane, 1, stepSize);
        m_renderWindow->GetInteractor()->SetInteractorStyle(customStyle);
        break;
    default:
        break;
    }
}

void Viewer3DWidget::setBlendMode(Viewer3D::BlendMode mode)
{
    switch (mode) {
    case Viewer3D::BlendMode::Composite:
        m_mapper->SetBlendModeToComposite();
        m_renderWindow->Render();
        break;
    case Viewer3D::BlendMode::Additive:
        m_mapper->SetBlendModeToAdditive();
        m_renderWindow->Render();
        break;
    case Viewer3D::BlendMode::MaximumIntensity:
        m_mapper->SetBlendModeToMaximumIntensity();
        m_renderWindow->Render();
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
