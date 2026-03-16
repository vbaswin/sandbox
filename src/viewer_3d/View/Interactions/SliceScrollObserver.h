#pragma once
#include "vtkCommand.h"
#include "vtkImagePlaneWidget.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkWeakPointer.h"

namespace Viewer3D::Interaction {

class SliceScrollObserver : public vtkCommand
{
    static SliceScrollObserver *New() { return new SliceScrollObserver; }
    vtkTypeMacro(SliceScrollObserver, vtkCommand);

    void SetImagPlaneWidget(vtkImagePlaneWidget *widget) { m_imagePlaneWidget = widget; }

    void Execute(vtkObject *caller, unsigned long eventId, void * /*callback*/) override
    {
        if (!m_imagePlaneWidget || !m_imagePlaneWidget->GetEnabled()) {
            return;
        }
        auto *interactor = vtkRenderWindowInteractor::SafeDownCast(caller);
        if (!interactor) {
            return;
        }

        const int currentSlice = m_imagePlaneWidget->GetSliceIndex();
        if (eventId == vtkCommand::MouseWheelForwardEvent) {
            m_imagePlaneWidget->SetSliceIndex(currentSlice + 1);
        } else if (eventId == vtkCommand::MouseWheelBackwardEvent) {
            m_imagePlaneWidget->SetSliceIndex(currentSlice - 1);
        }

        // stop this event from progression furthur, to prevent default action
        this->AbortFlagOn();
        interactor->Render(); //force re-render to visuall apply the new slice
    }

protected:
    SliceScrollObserver() = default;
    ~SliceScrollObserver() override = default;

private:
    // weak pointer, circular dependency problem
    vtkWeakPointer<vtkImagePlaneWidget> m_imagePlaneWidget;
};

} // namespace Viewer3D::Interaction
