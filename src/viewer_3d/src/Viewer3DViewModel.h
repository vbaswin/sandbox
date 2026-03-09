#pragma once

#include <QObject>
#include "src/viewer_3d/inc/IViewer3DViewModel.h"
#include "volumepipeline.h"

class Viewer3DViewModel : public QObject, public Viewer3D::Interfaces::IViewer3DViewModel
{
    Q_OBJECT
public:
    explicit Viewer3DViewModel(std::shared_ptr<VolumePipeline>, QObject *parent = nullptr);
    void loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                        std::pair<double, double> scalarRange);
    VolumePipeline *getPipeline() const;
    vtkImageData *getImageData();
    vtkVolumeProperty *getVolumeProperty();

signals:
    void dataPropertyReady();
private slots:
    void setRangeStart(int val);
    // void onDataPropertyReady();

private:
    std::shared_ptr<VolumePipeline> m_pipeline;
};
