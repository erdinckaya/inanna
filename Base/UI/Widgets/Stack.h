//
// Created by Erdınc Kaya on 2018-12-11.
//

#ifndef INANNA_STACK_H
#define INANNA_STACK_H

#include "../Types.h"

namespace Inanna {
    struct Stack {
        explicit Stack(DirectionType direction) : direction(direction) {}

        DirectionType direction;
    };
}
#endif //INANNA_STACK_H
