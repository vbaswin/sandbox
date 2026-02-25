#pragma once

#include <QObject>
#include "volumepipeline.h"

class Viewer3DViewModel : public QObject
{
    Q_OBJECT
public:
    explicit Viewer3DViewModel(QObject *parent = nullptr);
    void loadVolumeData(vtkSmartPointer<vtkImageData> imageData, double scalarRange[2]);
    vtkSmartPointer<vtkVolume> getVolume() const;

signals:
    void volumeReady();
    void requestRender();

private:
    VolumePipeline m_pipeline;
};
