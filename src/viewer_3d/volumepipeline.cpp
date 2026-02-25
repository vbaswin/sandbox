#include "volumepipeline.h"

VolumePipeline::VolumePipeline()
{
    m_mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    m_mapper->AutoAdjustSampleDistancesOn();
    m_mapper->SetBlendModeToComposite();

    m_opacityPiecewiseFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    m_colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();

    m_prop = vtkSmartPointer<vtkVolumeProperty>::New();
    m_prop->ShadeOff();

    m_volume = vtkSmartPointer<vtkVolume>::New();
    m_volume->SetMapper(m_mapper);
    m_volume->SetProperty(m_prop);
}

void VolumePipeline::SetInputData(vtkSmartPointer<vtkImageData> imageData, double scalarRange[2])
{
    m_mapper->SetInputData(imageData);
    setupTransferFunctions(scalarRange);
}

void VolumePipeline::setupTransferFunctions(double range[2])
{
    m_opacityPiecewiseFunction->RemoveAllPoints();
    m_opacityPiecewiseFunction->AddPoint(range[0], 0.0);  // water
    m_opacityPiecewiseFunction->AddPoint(-1000, 0.0);     // water
    m_opacityPiecewiseFunction->AddPoint(0, 0.05);        // water
    m_opacityPiecewiseFunction->AddPoint(300, 0.2);       // bone
    m_opacityPiecewiseFunction->AddPoint(700, 0.7);       // bone
    m_opacityPiecewiseFunction->AddPoint(range[1], 1.00); // dense bone

    m_colorTransferFunction->RemoveAllPoints();
    m_colorTransferFunction->AddRGBPoint(range[0], 0.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(range[1], 1.0, 1.0, 1.0);

    m_prop->SetScalarOpacity(m_opacityPiecewiseFunction);
    m_prop->SetColor(m_colorTransferFunction);
}

vtkSmartPointer<vtkVolume> VolumePipeline::GetVolume() const
{
    return m_volume;
}
