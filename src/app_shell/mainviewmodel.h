#pragma once

#include <QObject>
#include "dicom/DicomLoader.h"
#include "src/viewer_3d/inc/IViewer3DViewModel.h"
// #include "viewer_3d/Viewer3DViewModel.h"

class MainViewModel : public QObject
{
    Q_OBJECT
public:
    explicit MainViewModel(std::shared_ptr<Viewer3D::Interfaces::IViewer3DViewModel> viewer3DVM,
                           QObject *parent = nullptr);

    //     Viewer3DViewModel *getViewer3DViewModel() const;
    void executeInitialAppLoad(const char *path);
    //     void sliderChanged(int val);
    void requestBlendModeChange(Viewer3D::BlendMode);
    void setRangeStart(int val);

private:
    std::shared_ptr<DicomLoader> m_dicomLoader;
    std::shared_ptr<Viewer3D::Interfaces::IViewer3DViewModel> m_viewer3DVM;
};
