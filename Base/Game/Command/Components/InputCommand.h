#include <utility>

//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_INPUTCOMMAND_H
#define INANNA_INPUTCOMMAND_H

#include <string>
#include <SDL_scancode.h>
#include <entityx/Entity.h>

#include "../../../../ThirdParty/Signals/Signal.h"

#include "../../../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"


namespace Inanna {
    typedef unsigned long CommandId;

    struct InputCommand {
        InputCommand(const entityx::Entity &character, const SDL_Scancode &key, const Uint32 time,
                     const bool &down = true,
                     const bool &interrupt = false) :
                character(character), key(key), down(down), interrupt(interrupt), time(time), id(Id++) {}

        entityx::Entity character;
        const SDL_Scancode key;
        bool down;
        bool interrupt;
        const Uint32 time;
        CommandId id;

    private:
        static CommandId Id;

    public:
        REFLECT()
    };
}

#endif //INANNA_INPUTCOMMAND_H
