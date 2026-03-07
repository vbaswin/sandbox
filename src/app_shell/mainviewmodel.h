#pragma once

#include <QObject>
#include "dicom/DicomLoader.h"
#include "src/viewer_3d/inc/IViewer3DViewModel.h"
// #include "viewer_3d/Viewer3DViewModel.h"

class MainViewModel : public QObject
{
    Q_OBJECT
public:
    explicit MainViewModel(QObject *parent = nullptr);
    ~MainViewModel() override;

    //     Viewer3DViewModel *getViewer3DViewModel() const;
    void executeInitialAppLoad(const char *path);
    // public slots:
    //     void sliderChanged(int val);

    // private:
    DicomLoader *m_dicomLoader;
    std::unique_ptr<Viewer3D::Interfaces::IViewer3DViewModel> m_viewer3DVM;
};
