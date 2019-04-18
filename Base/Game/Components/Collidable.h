//
// Created by Erdınc Kaya on 2019-04-18.
//

#ifndef INANNA_COLLIDABLE_H
#define INANNA_COLLIDABLE_H

#include "../../Util/Math/Rect.h"

namespace Inanna {
    struct Collidable {
        explicit Collidable(const Rectf &box = Rectf(0, 0, 0, 0)) : box(box) {}

        Rectf box;
    };
}

#endif //INANNA_COLLIDABLE_H
