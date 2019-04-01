//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_DAMAGERECEIVECOMMAND_H
#define INANNA_DAMAGERECEIVECOMMAND_H

#include <entityx/Entity.h>
#include "../../Components/UserKey.h"
#include "../../Util/Chrono.h"

namespace Inanna {
    struct DamageReceiveCommand {
        explicit DamageReceiveCommand(entityx::Entity source, entityx::Entity destination, float damage) :
                source(source), destination(destination), damage(damage), time(Chrono::Now()) {}

        entityx::Entity source;
        entityx::Entity destination;
        float damage;
        Uint32 time;

    };
}
#endif //INANNA_DAMAGERECEIVECOMMAND_H
