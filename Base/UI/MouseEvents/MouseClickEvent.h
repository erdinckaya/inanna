//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSECLICKEVENT_H
#define INANNA_MOUSECLICKEVENT_H

#include <entityx/Entity.h>
#include <SDL_events.h>

namespace Inanna {
    struct MouseClickEvent {
        explicit MouseClickEvent(entityx::Entity entity, const SDL_MouseButtonEvent &mouseEvent) : entity(entity),
                                                                                                  mouseEvent(mouseEvent){}

        entityx::Entity entity;
        SDL_MouseButtonEvent mouseEvent;
    };
}
#endif //INANNA_MOUSECLICKEVENT_H
