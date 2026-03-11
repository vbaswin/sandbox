#pragma once
#include "Types.h"
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
    virtual void requestBlendModeChange(Viewer3D::BlendMode mode) = 0;
    virtual void setRangeStart(int val) = 0;
};

} // namespace Viewer3D::Interfaces
