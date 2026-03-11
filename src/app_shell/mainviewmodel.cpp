#include "mainviewmodel.h"
#include <QDebug>
#include <utility>

MainViewModel::MainViewModel(std::shared_ptr<Viewer3D::Interfaces::IViewer3DViewModel> viewer3DVM,
                             QObject *parent)
    : QObject{parent}
    , m_dicomLoader(std::make_shared<DicomLoader>())
    , m_viewer3DVM(viewer3DVM)
{
    // m_dicomLoader = new DicomLoader();
    // m_viewer3DViewModel = new Viewer3DViewModel(this);
}

void MainViewModel::requestBlendModeChange(Viewer3D::BlendMode mode)
{
    m_viewer3DVM->requestBlendModeChange(mode);
}

MainViewModel::~MainViewModel()
{
    // delete m_dicomLoader;
}

// Viewer3DViewModel *MainViewModel::getViewer3DViewModel() const
// {
//     return m_viewer3DViewModel;
// }

// void MainViewModel::sliderChanged(int val)
// {
//     getViewer3DViewModel();
//     m_viewer3DViewModel->getPipeline()->setRangeStart(val);
// }

void MainViewModel::executeInitialAppLoad(const char *path)
{
    if (m_dicomLoader->loadDirectory(path)) {
        double range[2];
        m_dicomLoader->GetScalarRange(range);
        std::pair<double, double> tmp_range{range[0], range[1]};
        qDebug() << "Dicom loaded successfully. Range: " << range[0] << " to " << range[1];

        m_viewer3DVM->loadVolumeData(m_dicomLoader->GetOutputData(), tmp_range);
    } else {
        qDebug() << "Failed to load Dicom";
    }
}
