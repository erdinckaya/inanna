//
// Created by Erdınc Kaya on 2019-04-19.
//

#ifndef INANNA_GIZMO_H
#define INANNA_GIZMO_H

namespace Inanna {
    struct Gizmo {
        explicit Gizmo(const bool &drawBoundingBox = false) : drawBoundingBox(drawBoundingBox) {}

        bool drawBoundingBox;

        REFLECT()
    };
}

#endif //INANNA_GIZMO_H
