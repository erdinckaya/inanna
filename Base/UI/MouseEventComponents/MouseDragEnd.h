//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEDRAGEND_H
#define INANNA_MOUSEDRAGEND_H

#include "../Types.h"

namespace Inanna {
    struct MouseDragEnd {
        explicit MouseDragEnd(MouseMotionCallback callback) : callback(std::move(callback)) {}

        MouseMotionCallback callback;
    };
}
#endif //INANNA_MOUSEDRAGEND_H
