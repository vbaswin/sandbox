#pragma once
#include <QObject>
#include "vtkColorTransferFunction.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkImageData.h"
#include "vtkPiecewiseFunction.h"
#include "vtkSmartPointer.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"

class VolumePipeline : public QObject
{
    Q_OBJECT;

public:
    explicit VolumePipeline(QObject *parent = nullptr);
    void SetInputData(vtkSmartPointer<vtkImageData> imageData,
                      std::pair<double, double> scalarRange);
    vtkSmartPointer<vtkVolume> GetVolume() const;
    void setRange(std::pair<double, double>);
    void setRangeStart(int range);

private:
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_mapper;
    vtkSmartPointer<vtkPiecewiseFunction> m_opacityPiecewiseFunction;
    vtkSmartPointer<vtkColorTransferFunction> m_colorTransferFunction;
    vtkSmartPointer<vtkVolumeProperty> m_prop;
    vtkSmartPointer<vtkVolume> m_volume;
    void setupTransferFunctions();

    int m_rangeStart = -1000;
    std::pair<double, double> m_range;
    // signals:
    //     void reRender();
};
