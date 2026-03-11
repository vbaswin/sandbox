#pragma once
#include <QObject>
#include "src/viewer_3d/inc/IModel.h"
#include "vtkColorTransferFunction.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkImageData.h"
#include "vtkPiecewiseFunction.h"
#include "vtkSmartPointer.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"

class VolumePipeline : public QObject, public IModel
{
    Q_OBJECT;

public:
    explicit VolumePipeline(QObject *parent = nullptr);
    void SetInputData(vtkSmartPointer<vtkImageData> imageData,
                      std::pair<double, double> scalarRange);
    void setRange(std::pair<double, double>);
    void setRangeStart(int range);
    vtkVolumeProperty *getVolumeProperty();
    vtkImageData *getImageData();

private:
    vtkSmartPointer<vtkPiecewiseFunction> m_opacityPiecewiseFunction;
    vtkSmartPointer<vtkColorTransferFunction> m_colorTransferFunction;
    vtkSmartPointer<vtkVolumeProperty> m_prop;
    void setupTransferFunctions();

    int m_rangeStart = 0;
    vtkSmartPointer<vtkImageData> m_imageData;
    std::pair<double, double> m_range;
signals:
    void dataPropertyReady();
};
