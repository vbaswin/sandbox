#pragma once

#include <QWidget>
enum BlendMode { Composite, MaximumIntensity, Additive };

namespace Viewer3D::Interfaces {

class IViewer3D
{
public:
    // [[nodiscard]] explicit IViewer3D();
    virtual ~IViewer3D() = default; // polymorphic destruction
    [[nodiscard]] virtual QWidget *asWidget() = 0;
};
} // namespace Viewer3D::Interfaces
