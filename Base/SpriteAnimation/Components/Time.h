//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_TIME_H
#define INANNA_TIME_H

#include "../../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

namespace Inanna {
    struct Time {
        explicit Time(const float &time): time(time) {}

        float time;

        REFLECT()
    };
}

#endif //INANNA_TIME_H
