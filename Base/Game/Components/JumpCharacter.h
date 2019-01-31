#include <utility>

//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPCHARACTER_H
#define INANNA_JUMPCHARACTER_H


#include <entityx/config.h>
#include "../../Util/Math/Vec2.h"
#include "../../../Assets/AnimationData.h"

#include <SDL_types.h>

namespace Inanna {
    struct JumpCharacter {
        explicit JumpCharacter(const Vecf &direction, int speed,
                               SpriteAnimData animData, Uint32 startTime) : direction(direction),
                                                                            speed(speed),
                                                                            animData(std::move(
                                                                                    animData)),
                                                                            time(0),
                                                                            startTime(startTime),
                                                                            longJump(false) {}


        int speed;
        Vecf direction;
        float time;
        SpriteAnimData animData;
        Uint32 startTime;
        bool longJump;


        REFLECT()
    };
}

#endif //INANNA_JUMPCHARACTER_H
