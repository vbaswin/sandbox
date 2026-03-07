#pragma once
#include "vtkImageData.h"
#include "vtkSmartPointer.h"

namespace Viewer3D::Interfaces {

class IViewer3DViewModel
{
public:
    virtual ~IViewer3DViewModel() = default;

    virtual void loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                                std::pair<double, double> scalarRange)
        = 0;
};

} // namespace Viewer3D::Interfaces
