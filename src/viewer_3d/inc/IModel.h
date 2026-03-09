#pragma once
#include "vtkImageData.h"
#include "vtkSmartPointer.h"


class IModel
{
public:
    virtual void SetInputData(vtkSmartPointer<vtkImageData>, std::pair<double, double> scalarRangE)
        = 0;
    // virtual void setBlendMode(BlendMode) = 0;
    virtual void setRangeStart(int) = 0;
};
