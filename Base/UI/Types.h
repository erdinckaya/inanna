//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_TYPES_H
#define INANNA_TYPES_H

#include <entityx/Entity.h>
#include <SDL_events.h>

namespace Inanna {
    typedef std::function<void(entityx::Entity, SDL_MouseButtonEvent)> MouseButtonCallback;
    typedef std::function<void(entityx::Entity, SDL_MouseMotionEvent)> MouseMotionCallback;

    enum ButtonState {
        None = -1,
        Idle = 0,
        Over = 1,
        Pressed = 2,
        Disable = 3,
        Count = 4,
    };

    enum MouseButtonState {
        Finger,
        MouseLeft,
        MouseRight,
        MouseMiddle,
    };
}

#endif //INANNA_TYPES_H
