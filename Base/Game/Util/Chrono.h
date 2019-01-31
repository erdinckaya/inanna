//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_CHRONO_H
#define INANNA_CHRONO_H

#include <SDL_types.h>
#include <SDL_timer.h>

namespace Inanna {
    struct Chrono {
        static Uint32 Now() {
            return SDL_GetTicks();
        }
    };
}

#endif //INANNA_CHRONO_H
