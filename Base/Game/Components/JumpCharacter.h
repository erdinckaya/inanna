#include <utility>

//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPCHARACTER_H
#define INANNA_JUMPCHARACTER_H


#include <entityx/config.h>
#include "../../Util/Math/Vec2.h"
#include "../../../Assets/AnimationData.h"
#include "../../Util/Math/Physics.h"
#include "../Util/Chrono.h"

#include <SDL_types.h>

namespace Inanna {
    struct JumpCharacter {
        explicit JumpCharacter(SpriteAnimData animData, float distance, float risingTime, float vX,
                               Uint32 startTime = Chrono::Now()) :
                animData(std::move(animData)), startTime(startTime), distance(distance), risingTime(risingTime), vX(vX),
                totalTime(0), longJump(true) {}

        SpriteAnimData animData;
        Uint32 startTime;
        float distance;       // total jump distance
        float risingTime; // seconds
        float totalTime;  // seconds
        float vX;
        bool longJump;

        REFLECT()
    };
}

#endif //INANNA_JUMPCHARACTER_H
