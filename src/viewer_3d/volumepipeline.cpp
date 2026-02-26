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

void VolumePipeline::setRangeStart(int start)
{
    m_rangeStart = start;
    // setupTransferFunctions();
}

void VolumePipeline::setupTransferFunctions(double range[2])
{
    m_opacityPiecewiseFunction->RemoveAllPoints();
    m_opacityPiecewiseFunction->AddPoint(range[0] + m_rangeStart, 0.0);  // water
    m_opacityPiecewiseFunction->AddPoint(-1000 + m_rangeStart, 0.0);     // water
    m_opacityPiecewiseFunction->AddPoint(0 + m_rangeStart, 0.05);        // water
    m_opacityPiecewiseFunction->AddPoint(300 + m_rangeStart, 0.2);       // bone
    m_opacityPiecewiseFunction->AddPoint(700 + m_rangeStart, 0.7);       // bone
    m_opacityPiecewiseFunction->AddPoint(range[1] + m_rangeStart, 1.00); // dense bone

    m_colorTransferFunction->RemoveAllPoints();

    // Air & Lungs (Invisible/Black)
    // We keep values below -200 dark to prevent background noise from clouding the render
    m_colorTransferFunction->AddRGBPoint(range[0] + m_rangeStart, 0.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(-1000 + m_rangeStart, 0.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(-200 + m_rangeStart, 0.0, 0.0, 0.0);

    // Fat (Pale Yellow/Orange)
    m_colorTransferFunction->AddRGBPoint(-100, 0.8, 0.7, 0.4);

    // Water / Soft Tissue / Blood (Fleshy / Red-Pink tones)
    m_colorTransferFunction->AddRGBPoint(0, 0.8, 0.4, 0.3);
    m_colorTransferFunction->AddRGBPoint(45, 0.9, 0.5, 0.4);

    // Soft Bone / Cartilage (Beige transition)
    m_colorTransferFunction->AddRGBPoint(150, 0.95, 0.85, 0.75);

    // Hard Bone (Off-white to pure white)
    m_colorTransferFunction->AddRGBPoint(300, 1.0, 0.95, 0.9);
    m_colorTransferFunction->AddRGBPoint(1000, 1.0, 1.0, 1.0);
    m_colorTransferFunction->AddRGBPoint(range[1], 1.0, 1.0, 1.0);

    m_prop->SetScalarOpacity(m_opacityPiecewiseFunction);
    m_prop->SetColor(m_colorTransferFunction);
}

vtkSmartPointer<vtkVolume> VolumePipeline::GetVolume() const
{
    return m_volume;
}
