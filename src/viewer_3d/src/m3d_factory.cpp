#include "src/viewer_3d/inc/m3d_factory.h"
#include "VolumePipeline.h"

// M3D_factory::M3D_factory() {}
static std::shared_ptr<IModel> createModel()
{
    return std::shared_ptr<VolumePipeline>();
}
