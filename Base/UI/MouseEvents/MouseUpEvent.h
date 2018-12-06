//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEUPEVENT_H
#define INANNA_MOUSEUPEVENT_H

#include <entityx/Entity.h>

namespace Inanna {
    struct MouseUpEvent {
        explicit MouseUpEvent(entityx::Entity entity, const SDL_MouseButtonEvent &mouseEvent) : entity(entity),
                                                              mouseEvent(mouseEvent) {}

        entityx::Entity entity;
        SDL_MouseButtonEvent mouseEvent;
    };
}
#endif //INANNA_MOUSEUPEVENT_H
