//
// Created by Erdınc Kaya on 2019-04-25.
//

#ifndef INANNA_CAMERA_H
#define INANNA_CAMERA_H

#include "../../Util/Math/Rect.h"

namespace Inanna {
    struct Camera {
        explicit Camera(const Rectf &port, const Vecf &posDiff = Vecf(0, 0)) : port(port) {}

        Rectf port;
    };
}


#endif //INANNA_CAMERA_H
