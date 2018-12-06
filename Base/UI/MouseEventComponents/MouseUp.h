#include <utility>

//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEUPLISTENER_H
#define INANNA_MOUSEUPLISTENER_H

#include "../Types.h"

namespace Inanna {
    struct MouseUp {
        explicit MouseUp(MouseButtonCallback callback) : callback(std::move(callback)) {}

        MouseButtonCallback callback;
    };
}
#endif //INANNA_MOUSEUPLISTENER_H
