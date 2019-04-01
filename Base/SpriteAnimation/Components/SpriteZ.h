//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_SPRITEZ_H
#define INANNA_SPRITEZ_H

#include "../../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

namespace Inanna {
    struct SpriteZ {
        explicit SpriteZ(const int &z): z(z) {}

        int z;

        REFLECT()
    };
}
#endif //INANNA_SPRITEZ_H
