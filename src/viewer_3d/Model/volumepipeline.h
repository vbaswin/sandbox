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
#include <array>

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
    std::array<double, 3> getSpacing() { return m_spacing; };

private:
    vtkSmartPointer<vtkPiecewiseFunction> m_opacityPiecewiseFunction;
    vtkSmartPointer<vtkColorTransferFunction> m_colorTransferFunction;
    vtkSmartPointer<vtkVolumeProperty> m_prop;
    void setupTransferFunctions();

    int m_rangeStart = -650;
    vtkSmartPointer<vtkImageData> m_imageData;
    std::array<double, 3> m_spacing{1.0, 1.0, 1.0};
    std::pair<double, double> m_range;
signals:
    void dataPropertyReady();
};
