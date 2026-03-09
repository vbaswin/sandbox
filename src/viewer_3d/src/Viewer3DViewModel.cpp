#include "viewer3dviewmodel.h"

Viewer3DViewModel::Viewer3DViewModel(std::shared_ptr<VolumePipeline> pipeline, QObject *parent)
    : QObject{parent}
    , m_pipeline(pipeline)
{
    connect(m_pipeline.get(), &VolumePipeline::dataPropertyReady, this, [=]() {
        emit dataPropertyReady();
    });
}
void Viewer3DViewModel::loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                                       std::pair<double, double> scalarRange)
{
    if (!imageData)
        return;

    m_pipeline->SetInputData(imageData, scalarRange);
}

void Viewer3DViewModel::setRangeStart(int val)
{
    m_pipeline->setRangeStart(val);
    // emit reRender();
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
