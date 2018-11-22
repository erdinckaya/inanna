//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_ROTATION_H
#define INANNA_ROTATION_H

#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct Rotation {
        explicit Rotation(const float &rotation = 0) : rotation(rotation) {}
        const float rotation;
    };
}
#endif //INANNA_ROTATION_H
