#include <utility>

//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_MOVECOMMAND_H
#define INANNA_MOVECOMMAND_H

#include <string>
#include <SDL_scancode.h>
#include <entityx/Entity.h>

namespace Inanna {
    typedef unsigned long CommandId;

    struct InputCommand {
        InputCommand(const entityx::Entity &character, const SDL_Scancode &key, const bool &down = true,
                     const bool &interrupt = false) :
                character(character), key(key), down(down), interrupt(interrupt), id(Id++) {}

        entityx::Entity character;
        const SDL_Scancode key;
        bool down;
        bool interrupt;

        CommandId id;

    private:
        static CommandId Id;
    };
}

#endif //INANNA_MOVECOMMAND_H
