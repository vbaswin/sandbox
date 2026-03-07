#include "volumepipeline.h"
#include <QDebug>
#include "src/viewer_3d/inc/Types.h"

VolumePipeline::VolumePipeline(QObject *parent)
    : QObject(parent)
{
    m_opacityPiecewiseFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    m_colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();

    m_prop = vtkSmartPointer<vtkVolumeProperty>::New();

    // 1. Turn on shading (Absolutely required for 3D depth)
    m_prop->ShadeOn();

    // 2. Ambient light (Keep low so the dark brown shadows we set earlier stay dark)
    m_prop->SetAmbient(0.15);

    // 3. Diffuse light (How much the main color shows up when hit by light)
    m_prop->SetDiffuse(0.80);

    // 4. Specular light (This creates the bright, glossy "shiny" reflections on the metal and bone edges)
    m_prop->SetSpecular(0.45);

    // 5. Specular Power (How sharp/pinpoint the shiny reflection is. Higher = glossier/more metallic)
    m_prop->SetSpecularPower(70.0);
    // m_prop->SetInterpolationTypeToNearest();
}

void VolumePipeline::SetInputData(vtkSmartPointer<vtkImageData> imageData,
                                  std::pair<double, double> scalarRange)
{
    m_imageData = imageData;
    setRange(scalarRange);
    setupTransferFunctions();
    emit dataPropertyReady();
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
    m_opacityPiecewiseFunction->RemoveAllPoints();
    m_colorTransferFunction->RemoveAllPoints();

    for (const auto &point : Module3D::preset) {
        double shiftedHU = point.hu + m_rangeStart;
        qDebug() << shiftedHU << " : " << point.hu;

        m_opacityPiecewiseFunction->AddPoint(shiftedHU, point.opacity);
        m_colorTransferFunction->AddRGBPoint(shiftedHU,
                                             static_cast<double>(point.r) / 255.0,
                                             static_cast<double>(point.g) / 255.0,
                                             static_cast<double>(point.b) / 255.0);
    }

    m_prop->SetScalarOpacity(m_opacityPiecewiseFunction);
    m_prop->SetColor(m_colorTransferFunction);
}

vtkVolumeProperty *VolumeProperty::getVolumeProperty()
{
    return m_prop;
}
vtkImageData *VolumeProperty::getImageData()
{
    return m_imageData;
}
