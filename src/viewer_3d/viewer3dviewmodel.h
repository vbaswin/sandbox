#pragma once

#include <QObject>
#include "volumepipeline.h"

class Viewer3DViewModel : public QObject
{
    Q_OBJECT
public:
    explicit Viewer3DViewModel(QObject *parent = nullptr);
    void loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                        std::pair<double, double> scalarRange);
    vtkSmartPointer<vtkVolume> getVolume() const;
    VolumePipeline *getPipeline() const;

signals:
    void volumeReady();
public slots:
    void setRangeStart(int val);

    // private slots:
    //     void onSliderChanged(int value);

private:
    std::unique_ptr<VolumePipeline> m_pipeline;
};
