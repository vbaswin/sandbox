#pragma once

#include <QString>
#include "vtkDICOMDirectory.h"
#include "vtkDICOMReader.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"

class DicomLoader
{
public:
    DicomLoader();
    bool loadDirectory(const char *);
    vtkSmartPointer<vtkImageData> GetOutputData() const;
    void GetScalarRange(double range[2]) const;

private:
    vtkSmartPointer<vtkDICOMDirectory> m_dir;
    vtkSmartPointer<vtkDICOMReader> m_reader;
};
