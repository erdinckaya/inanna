//
// Created by Erdınc Kaya on 2019-01-29.
//

#ifndef INANNA_CROUCH_H
#define INANNA_CROUCH_H

namespace Inanna {
    struct Crouch {
        explicit Crouch(const bool &down) : down(down) {}

        bool down;

        REFLECT()
    };
}
#endif //INANNA_CROUCH_H
