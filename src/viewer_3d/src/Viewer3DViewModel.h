#pragma once

#include <QObject>
#include "src/viewer_3d/inc/IViewer3DViewModel.h"
#include "volumepipeline.h"

class Viewer3DViewModel : public QObject, public Viewer3D::Interfaces::IViewer3DViewModel
{
    Q_OBJECT
public:
    explicit Viewer3DViewModel(std::unique_ptr<VolumePipeline>, QObject *parent = nullptr);
    void loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                        std::pair<double, double> scalarRange);
    vtkSmartPointer<vtkVolume> getVolume() const;
    VolumePipeline *getPipeline() const;

signals:
    void volumeReady();
    void reRender();
public slots:
    void setRangeStart(int val);

private:
    std::unique_ptr<VolumePipeline> m_pipeline;
};
