//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_MOUSEMOTION_H
#define INANNA_MOUSEMOTION_H

#include <SDL_events.h>

namespace Inanna {
    // Unique
    struct MouseMotion {
        explicit MouseMotion() = default;

        explicit MouseMotion(const SDL_MouseMotionEvent &event) : event(event) {};

        SDL_MouseMotionEvent event;
    };
}

#endif //INANNA_MOUSEMOTION_H
