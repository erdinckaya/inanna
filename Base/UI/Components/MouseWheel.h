//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_MOUSEWHEEL_H
#define INANNA_MOUSEWHEEL_H

#include <SDL_events.h>

namespace Inanna {
    // Unique
    struct MouseWheel {
        explicit MouseWheel() = default;

        explicit MouseWheel(const SDL_MouseWheelEvent &event) : event(event) {};

        SDL_MouseWheelEvent event;
    };
}

#endif //INANNA_MOUSEWHEEL_H
