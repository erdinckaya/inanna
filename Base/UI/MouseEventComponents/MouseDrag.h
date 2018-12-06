//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEMOVE_H
#define INANNA_MOUSEMOVE_H

#include "../Types.h"

namespace Inanna {
    struct MouseDrag {
        explicit MouseDrag(MouseMotionCallback callback) : callback(std::move(callback)) {}

        MouseMotionCallback callback;
    };
}
#endif //INANNA_MOUSEMOVE_H
