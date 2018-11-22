//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_SCALE_H
#define INANNA_SCALE_H

#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct Scalable {
        explicit Scalable(const Vecf &scale = Vecf(1, 1)) : scale(scale) {}
        Vecf scale;
    };
}
#endif //INANNA_SCALE_H
