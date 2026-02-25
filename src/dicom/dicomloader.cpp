#include "dicomloader.h"

DicomLoader::DicomLoader()
{
    m_dir = vtkSmartPointer<vtkDICOMDirectory>::New();
    m_reader = vtkSmartPointer<vtkDICOMReader>::New();
}

bool DicomLoader::loadDirectory(const QString &path)
{
    m_dir->SetDirectoryName(path.toStdString().c_str());
    m_dir->Update();
    if (m_dir->GetNumberOfSeries() == 0) {
        std::cerr << "No dicom series found in the directory ";
        return false;
    }
    m_reader->SetFileNames(m_dir->GetFileNamesForSeries(0));
    m_reader->Update();

    return true;
}

vtkSmartPointer<vtkImageData> DicomLoader::GetOutputData() const
{
    return m_reader->GetOutput();
}

void DicomLoader::GetScalarRange(double range[2]) const
{
    if (m_reader->GetOutput()) {
        m_reader->GetOutput()->GetScalarRange(range);
    } else {
        range[0] = 0.0;
        range[1] = 1.0;
    }
}
