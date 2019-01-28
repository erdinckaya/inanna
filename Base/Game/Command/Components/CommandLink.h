//
// Created by misterdortnal on 26.01.2019.
//

#ifndef INANNA_COMMANDLINK_H
#define INANNA_COMMANDLINK_H


#include <entityx/quick.h>

namespace Inanna {
    struct CommandLink {
        explicit CommandLink(const entityx::Entity &entity) : entity(entity) {}

        entityx::Entity entity;

        Gallant::Signal1<entityx::Entity> onExecuted;
    };
}

#endif //INANNA_COMMANDLINK_H
