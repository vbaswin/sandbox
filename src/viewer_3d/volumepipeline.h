#pragma once
#include "vtkColorTransferFunction.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkImageData.h"
#include "vtkPiecewiseFunction.h"
#include "vtkSmartPointer.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"

class VolumePipeline
{
public:
    VolumePipeline();
    void SetInputData(vtkSmartPointer<vtkImageData> imageData, double scalarRange[2]);
    vtkSmartPointer<vtkVolume> GetVolume() const;

private:
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_mapper;
    vtkSmartPointer<vtkPiecewiseFunction> m_opacityPiecewiseFunction;
    vtkSmartPointer<vtkColorTransferFunction> m_colorTransferFunction;
    vtkSmartPointer<vtkVolumeProperty> m_prop;
    vtkSmartPointer<vtkVolume> m_volume;
    void setupTransferFunctions(double range[2]);
};

