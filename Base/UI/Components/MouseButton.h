//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_MOUSEBUTTON_H
#define INANNA_MOUSEBUTTON_H

#include <SDL_events.h>

namespace Inanna {
    struct MouseButton {
        explicit MouseButton() = default;

        explicit MouseButton(const SDL_MouseButtonEvent &event) : event(event) {};

        SDL_MouseButtonEvent event;
    };
}

#endif //INANNA_MOUSEBUTTON_H
