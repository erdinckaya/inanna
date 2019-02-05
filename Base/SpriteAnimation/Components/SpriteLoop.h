//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_SPRITELOOP_H
#define INANNA_SPRITELOOP_H


#include "../../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

namespace Inanna {
    struct SpriteLoop {
        explicit SpriteLoop(const int &start, const int &end): start(start), end(end) {}

        int start;
        int end;

        REFLECT()
    };
}

#endif //INANNA_SPRITELOOP_H
