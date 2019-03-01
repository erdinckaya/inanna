//
// Created by Erdınc Kaya on 2019-03-01.
//

#ifndef INANNA_FACING_H
#define INANNA_FACING_H

namespace Inanna {
    struct Facing {
        explicit Facing(bool left = true) : left(left) {}

        bool left;

        REFLECT()
    };
}
#endif //INANNA_FACING_H
