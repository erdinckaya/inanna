//
// Created by Erdınc Kaya on 2019-01-23.
//

#ifndef INANNA_MOVECHARACTER_H
#define INANNA_MOVECHARACTER_H

namespace Inanna {
    struct MoveCharacter {
        explicit MoveCharacter(bool forward = true, float speed = 0.1f) : forward(forward), speed(speed) {}

        bool forward;
        float speed;
    };
}

#endif //INANNA_MOVECHARACTER_H
