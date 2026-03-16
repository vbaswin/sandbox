#pragma once

#include "src/viewer_3d/inc/Types.h"
#include "vtkInteractorStyleImage.h"
#include "vtkObjectFactory.h"
#include "vtkPlane.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"

namespace Viewer3D::Interaction {

class ClippingPlaneInteractorStyle : public vtkInteractorStyleImage
{
private:
    vtkSmartPointer<vtkPlane> m_clipPlane;
    // x 0, y 1, z 2
    // int m_axis{2};
    Viewer3D::viewOrientation m_orientation{Viewer3D::viewOrientation::Axial};
    double m_stepSize = 0.1;

    bool m_isAdjustingPlane{false};
    int m_accumulatedDrag{0}; // for slice by slice movement
    int m_dragSensitivity{5}; // how many screen pixels = 1 slice jump
    int m_lastY{0};

public:
    static ClippingPlaneInteractorStyle *New();
    vtkTypeMacro(ClippingPlaneInteractorStyle, vtkInteractorStyleImage);

    void SetClippingPlane(vtkSmartPointer<vtkPlane> plane,
                          Viewer3D::viewOrientation orientation,
                          double stepSize = 1.0)
    {
        m_clipPlane = plane;
        m_orientation = orientation;
        m_stepSize = stepSize;
        m_accumulatedDrag = 0;
    }

    void OnRightButtonDown() override
    {
        if (this->Interactor) {
            int *pos = this->Interactor->GetEventPosition();
            m_lastY = pos[1];
            m_isAdjustingPlane = true;
            m_accumulatedDrag = 0;
        }
    }
    void OnRightButtonUp() override { m_isAdjustingPlane = false; }

    void OnMouseMove() override
    {
        if (m_isAdjustingPlane) {
            int *pos = this->Interactor->GetEventPosition();
            int deltaY = pos[1] - m_lastY;
            m_lastY = pos[1];

            m_accumulatedDrag += deltaY;

            int dragSteps = m_accumulatedDrag / m_dragSensitivity;
            if (dragSteps) {
                m_clipPlane->Push(dragSteps * m_stepSize);
                this->Interactor->Render();
                m_accumulatedDrag %= m_dragSensitivity;
            }
        } else {
            vtkInteractorStyleImage::OnMouseMove(); // forwarding the signal
        }
    }

    // void onMouseWheelForward()
};

vtkStandardNewMacro(ClippingPlaneInteractorStyle);

} // namespace Viewer3D::Interaction
