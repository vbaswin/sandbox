#include "viewer3dviewmodel.h"

Viewer3DViewModel::Viewer3DViewModel(QObject *parent)
    : QObject{parent}
{}

void Viewer3DViewModel::loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                                       double scalarRange[2])
{
    if (!imageData)
        return;

    m_pipeline.SetInputData(imageData, scalarRange);
    emit volumeReady();
}

vtkSmartPointer<vtkVolume> Viewer3DViewModel::getVolume() const
{
    return m_pipeline.GetVolume();
}
