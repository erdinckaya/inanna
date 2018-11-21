//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_SDL_H
#define INANNA_SDL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>

namespace Inanna {
    class SDL {
    public:
        SDL(int flags);

        ~SDL();

    private:
        SDL(const SDL &); //Unimplemented
    };
}


#endif //INANNA_SDL_H
