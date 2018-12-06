//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEDOWNLISTENER_H
#define INANNA_MOUSEDOWNLISTENER_H

#include "../Types.h"

namespace Inanna {
    struct MouseDown {
        explicit MouseDown(MouseButtonCallback callback) : callback(std::move(callback)) {}

        MouseButtonCallback callback;
    };
}
#endif //INANNA_MOUSEDOWNLISTENER_H
