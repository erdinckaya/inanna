//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSECLICK_H
#define INANNA_MOUSECLICK_H

#include "../Types.h"

namespace Inanna {
    struct MouseClick {
        explicit MouseClick(MouseButtonCallback callback) : callback(std::move(callback)) {}

        MouseButtonCallback callback;
    };
}
#endif //INANNA_MOUSECLICK_H
