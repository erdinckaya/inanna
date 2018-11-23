//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_MOUSEINPUT_H
#define INANNA_MOUSEINPUT_H

#include <SDL_events.h>

namespace Inanna {
    // Unique
    struct MouseButton {
        explicit MouseButton() = default;

        explicit MouseButton(const SDL_MouseButtonEvent &event) : event(event) {};

        SDL_MouseButtonEvent event;
    };
}

#endif //INANNA_MOUSEINPUT_H
