//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEDRAGSTART_H
#define INANNA_MOUSEDRAGSTART_H

#include "../Types.h"

namespace Inanna {
    struct MouseDragStart {
        explicit MouseDragStart(MouseMotionCallback callback) : callback(std::move(callback)) {}

        MouseMotionCallback callback;
    };
}
#endif //INANNA_MOUSEDRAGSTART_H
