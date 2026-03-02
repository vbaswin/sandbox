#include "volumepipeline.h"
#include <QDebug>

VolumePipeline::VolumePipeline(QObject *parent)
    : QObject(parent)
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

void VolumePipeline::SetInputData(vtkSmartPointer<vtkImageData> imageData,
                                  std::pair<double, double> scalarRange)
{
    m_mapper->SetInputData(imageData);
    setRange(scalarRange);
    setupTransferFunctions();
}

void VolumePipeline::setRangeStart(int start)
{
    m_rangeStart = start;
    setupTransferFunctions();
    qDebug() << start;
}

void VolumePipeline::setRange(std::pair<double, double> range)
{
    m_range = range;
}

void VolumePipeline::setupTransferFunctions()
{
    // -------------------------------------------------------------
    // REFINED OPACITY TRANSFER FUNCTION (Piecewise)
    // -------------------------------------------------------------
    m_opacityPiecewiseFunction->RemoveAllPoints();

    m_opacityPiecewiseFunction->AddPoint(m_range.first + m_rangeStart, 0.0);

    // Completely transparent up to 120 HU (Air, fat, water, muscle are invisible)
    m_opacityPiecewiseFunction->AddPoint(120 + m_rangeStart, 0.0);

    // Very subtle start at 150 HU for the absolute edge of the bone.
    // A slight ramp here (0.0 to 0.05) prevents jagged "staircase" aliasing artifacts on the bone contour.
    m_opacityPiecewiseFunction->AddPoint(150 + m_rangeStart, 0.05);

    // Sharp cliff up to 200/300 HU is what creates the "solid shell" look of the outer bone
    m_opacityPiecewiseFunction->AddPoint(200 + m_rangeStart, 0.35);
    m_opacityPiecewiseFunction->AddPoint(300 + m_rangeStart, 0.55);

    // Gradual increase for denser, thicker cortical bone
    m_opacityPiecewiseFunction->AddPoint(500 + m_rangeStart, 0.75);
    m_opacityPiecewiseFunction->AddPoint(800 + m_rangeStart, 0.85);

    // Metal fixators/screws/wires (visible in your images) are much denser than bone (>2000 HU).
    // We make them completely opaque (1.0) so they look like solid metal objects.
    m_opacityPiecewiseFunction->AddPoint(2000 + m_rangeStart, 1.0);
    m_opacityPiecewiseFunction->AddPoint(m_range.second + m_rangeStart, 1.0);

    // -------------------------------------------------------------
    // REFINED COLOR TRANSFER FUNCTION (RGB)
    // -------------------------------------------------------------
    m_colorTransferFunction->RemoveAllPoints();

    m_colorTransferFunction->AddRGBPoint(m_range.first + m_rangeStart, 0.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(120 + m_rangeStart, 0.0, 0.0, 0.0);

    // 150-200 HU: The "Shadows" and porous surface details
    // Using a deeply saturated, dark red/brown gives rich contrast to the tiny pits in the bone
    m_colorTransferFunction->AddRGBPoint(150 + m_rangeStart, 0.15, 0.05, 0.02);
    m_colorTransferFunction->AddRGBPoint(200 + m_rangeStart, 0.45, 0.20, 0.08);

    // 300-500 HU: The primary "Bronze/Golden" bone core
    m_colorTransferFunction->AddRGBPoint(300 + m_rangeStart, 0.72, 0.43, 0.20);
    m_colorTransferFunction->AddRGBPoint(500 + m_rangeStart, 0.85, 0.65, 0.40);

    // 800-1200 HU: Dense ivory/white for the thickest cortical bone
    m_colorTransferFunction->AddRGBPoint(800 + m_rangeStart, 0.95, 0.88, 0.78);
    m_colorTransferFunction->AddRGBPoint(1200 + m_rangeStart, 1.00, 0.96, 0.90);

    // 2000+ HU: Metal implants (Screws, plates, wires visible in the scan)
    // We give this a slightly cool, bright silver/white to differentiate the metal from the ivory bone
    m_colorTransferFunction->AddRGBPoint(2000 + m_rangeStart, 0.95, 0.95, 1.00);
    m_colorTransferFunction->AddRGBPoint(3000 + m_rangeStart, 1.00, 1.00, 1.00);
    m_colorTransferFunction->AddRGBPoint(m_range.second + m_rangeStart, 1.00, 1.00, 1.00);

    m_prop->SetScalarOpacity(m_opacityPiecewiseFunction);
    m_prop->SetColor(m_colorTransferFunction);
}

vtkSmartPointer<vtkVolume> VolumePipeline::GetVolume() const
{
    return m_volume;
}
