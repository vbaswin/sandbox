#include "mainviewmodel.h"
#include <QDebug>

MainViewModel::MainViewModel(QObject *parent)
    : QObject{parent}
{
    m_dicomLoader = new DicomLoader();
    m_viewer3DViewModel = new Viewer3DViewModel(this);
}

MainViewModel::~MainViewModel()
{
    delete m_dicomLoader;
}

Viewer3DViewModel *MainViewModel::getViewer3DViewModel() const
{
    return m_viewer3DViewModel;
}

void MainViewModel::executeInitialAppLoad(const char *path)
{
    if (m_dicomLoader->loadDirectory(path)) {
        double range[2];
        m_dicomLoader->GetScalarRange(range);
        qDebug() << "Dicom loaded successfully. Range: " << range[0] << " to " << range[1];

        m_viewer3DViewModel->loadVolumeData(m_dicomLoader->GetOutputData(), range);
    }
}
