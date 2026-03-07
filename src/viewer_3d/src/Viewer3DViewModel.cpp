#include "viewer3dviewmodel.h"

Viewer3DViewModel::Viewer3DViewModel(std::unique_ptr<VolumePipeline> pipeline, QObject *parent)
    : QObject{parent}
    , m_pipeline(std::move(pipeline))
{}
void Viewer3DViewModel::loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                                       std::pair<double, double> scalarRange)
{
    if (!imageData)
        return;

    m_pipeline->SetInputData(imageData, scalarRange);
    emit volumeReady();
}

void Viewer3DViewModel::setRangeStart(int val)
{
    m_pipeline->setRangeStart(val);
    emit reRender();
}

vtkSmartPointer<vtkVolume> Viewer3DViewModel::getVolume() const
{
    return m_pipeline->GetVolume();
}

VolumePipeline *Viewer3DViewModel::getPipeline() const
{
    return m_pipeline.get();
}
