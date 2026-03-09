#pragma once
#include <QMetaType>
#include <vector>

namespace Viewer3D {

struct TransferPoint
{
    double hu; // hounsfield units
    double opacity;
    double r, g, b;
};

// prevent multiple definition linker errors
inline const std::vector<TransferPoint> preset
    = {{-100, 0.00, 205, 153, 46}, // fat
       {-50, 0.2, 227, 211, 178},
       {10, 0.21, 222, 142, 142}, // muscle/ blood/ soft tissue
       {40, 0.4, 215, 109, 84},
       {150, 0.41, 254, 210, 161}, // spongy bone/ cartilage
       {300, 0.6, 219, 183, 127},
       {700, 0.61, 251, 236, 206}, // dense cortical bone
       {1500, 0.8, 167, 163, 152},
       {2000, 0.81, 230, 230, 232}, // solid metal
       {3000, 1.0, 111, 105, 107}};

enum viewOrientation { Axial, Coronal, Sagittal, Main3D };
enum BlendMode { Composite, MaximumIntensity, Additive };

} // namespace Viewer3D

Q_DECLARE_METATYPE(Viewer3D::BlendMode);
