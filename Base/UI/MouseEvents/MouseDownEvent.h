//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEDOWNEVENT_H
#define INANNA_MOUSEDOWNEVENT_H

#include <entityx/Entity.h>

namespace Inanna {
    struct MouseDownEvent {
        explicit MouseDownEvent(entityx::Entity entity, const SDL_MouseButtonEvent &mouseEvent) : entity(entity),
                                                                mouseEvent(mouseEvent){}

        entityx::Entity entity;
        SDL_MouseButtonEvent mouseEvent;
    };
}
#endif //INANNA_MOUSEDOWNEVENT_H
