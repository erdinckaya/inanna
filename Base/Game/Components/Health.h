//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_HEALTH_H
#define INANNA_HEALTH_H

#include "../../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

#include <entityx/Entity.h>

namespace Inanna {
    struct Health {
        explicit Health(const float &health) : health(health) {}

        float health;

        REFLECT()
    };
}


#endif //INANNA_HEALTH_H
