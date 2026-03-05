#pragma once
#include "src/viewer_3d/inc/IModel.h"
#include <memory>

class M3D_factory
{
public:
    static std::shared_ptr<IModel> createModel();
};
