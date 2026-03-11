#include "src/viewer_3d/ViewModel/viewer3dviewmodel.h"
#include <QDebug>

Viewer3DViewModel::Viewer3DViewModel(std::shared_ptr<VolumePipeline> pipeline, QObject *parent)
    : QObject{parent}
    , m_pipeline(pipeline)
{
    connect(m_pipeline.get(), &VolumePipeline::dataPropertyReady, this, [=]() {
        emit dataPropertyReady();
    });
    connect(m_pipeline.get(), &VolumePipeline::propertyChanged, this, [this]() {
        emit renderRequested();
    });
}
void Viewer3DViewModel::loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                                       std::pair<double, double> scalarRange)
{
    if (!imageData)
        return;

    m_pipeline->SetInputData(imageData, scalarRange);
}

void Viewer3DViewModel::requestBlendModeChange(Viewer3D::BlendMode mode)
{
    emit blendModeChanged(mode);
}

std::array<double, 3> Viewer3DViewModel::getSpacing()
{
    return m_pipeline->getSpacing();
}

void Viewer3DViewModel::setRangeStart(int val)
{
    m_pipeline->setRangeStart(val);
    // emit reRender();
    qDebug() << "range: ";
}

void Viewer3DViewModel::setOrientation(Viewer3D::viewOrientation orient)
{
    m_orient = orient;
}
Viewer3D::viewOrientation Viewer3DViewModel::getorientation()
{
    return m_orient;
}

vtkImageData *Viewer3DViewModel::getImageData()
{
    return m_pipeline->getImageData();
}
vtkVolumeProperty *Viewer3DViewModel::getVolumeProperty()
{
    return m_pipeline->getVolumeProperty();
}

VolumePipeline *Viewer3DViewModel::getPipeline() const
{
    return m_pipeline.get();
}
