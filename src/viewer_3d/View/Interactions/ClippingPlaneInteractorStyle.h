#pragma once

#include "vtkInteractorStyleImage.h"
#include "vtkObjectFactory.h"
#include "vtkPlane.h"
#include "vtkSmartPointer.h"

namespace Viewer3D::Interactions {

class ClippingPlaneInteractorStyle : public vtkInteractorStyleImage
{
private:
    vtkSmartPointer<vtkPlane> m_clipPlane;
    // x 0, y 1, z 2
    int m_axis{2};
    double m_stepSize = 0.1;

public:
    static ClippingPlaneInteractorStyle *New();
    vtkTypeMacro(ClippingPlaneInteractorStyle, vtkInteractorStyleImage);

    void SetClippingPlane(vtkSmartPointer<vtkPlane> plane, int axis, double stepSize = 1.0)
    {
        m_clipPlane = plane;
        m_axis = axis;
        m_stepSize = stepSize;
    }

    // void onMouseWheelForward()
};

vtkStandardNewMacro(ClippingPlaneInteractorStyle);

} // namespace Viewer3D::Interactions
