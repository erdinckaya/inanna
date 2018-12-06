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
}

#endif //INANNA_TYPES_H
