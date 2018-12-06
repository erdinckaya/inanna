//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEDRAGENDEVENT_H
#define INANNA_MOUSEDRAGENDEVENT_H
#include <entityx/Entity.h>
#include <SDL_events.h>

namespace Inanna {
    struct MouseDragEndEvent {
        explicit MouseDragEndEvent(entityx::Entity entity, const SDL_MouseMotionEvent &mouseEvent) : entity(entity),
                                                                                                       mouseEvent(mouseEvent) {}

        entityx::Entity entity;
        SDL_MouseMotionEvent mouseEvent;
    };
}
#endif //INANNA_MOUSEDRAGENDEVENT_H
