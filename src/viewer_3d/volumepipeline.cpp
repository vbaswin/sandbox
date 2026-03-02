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

struct TransferPoint
{
    double hu; // hounsfield units
    double opacity;
    double r, g, b;
};

std::vector<TransferPoint> preset = {{-100, 0.00, 205, 153, 46}, // fat
                                     {-50, 0.2, 227, 211, 178},
                                     {10, 0.21, 222, 142, 142}, // muscle/ blood/ soft tissue
                                     {40, 0.4, 215, 109, 84},
                                     {150, 0.41, 254, 210, 161}, // spongy bone/ cartilage
                                     {300, 0.6, 219, 183, 127},
                                     {700, 0.61, 251, 236, 206}, // dense cortical bone
                                     {1500, 0.8, 222, 205, 184},
                                     {2000, 0.81, 230, 230, 232}, // solid metal
                                     {3000, 1.0, 111, 105, 107}};

void VolumePipeline::setupTransferFunctions()
{
    m_opacityPiecewiseFunction->RemoveAllPoints();
    m_colorTransferFunction->RemoveAllPoints();

    for (const auto &point : preset) {
        double shiftedHU = point.hu + m_rangeStart;

        m_opacityPiecewiseFunction->AddPoint(shiftedHU, point.opacity);
        m_colorTransferFunction->AddRGBPoint(shiftedHU,
                                             point.r / 255.0,
                                             point.g / 255.0,
                                             point.b / 255.0);
    }

    m_prop->SetScalarOpacity(m_opacityPiecewiseFunction);
    m_prop->SetColor(m_colorTransferFunction);
}

vtkSmartPointer<vtkVolume> VolumePipeline::GetVolume() const
{
    return m_volume;
}
