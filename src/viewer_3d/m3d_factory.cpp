#include "src/viewer_3d/inc/m3d_factory.h"
#include "src/viewer_3d/Model/VolumePipeline.h"

// M3D_factory::M3D_factory() {}
static std::shared_ptr<IModel> createModel()
{
    return std::shared_ptr<VolumePipeline>();
}
