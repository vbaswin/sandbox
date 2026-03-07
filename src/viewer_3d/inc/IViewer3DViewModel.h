#pragma once
#include "src/viewer_3d/src/Viewer3DViewModel.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"

namespace Viewer3D::Interfaces {

class IViewer3DViewModel
{
public:
    virtual ~IViewer3DViewModel() = default;

    void loadVolumeData(vtkSmartPointer<vtkImageData> imageData,
                        std::pair<double, double> scalarRange);
};

} // namespace Viewer3D::Interfaces
