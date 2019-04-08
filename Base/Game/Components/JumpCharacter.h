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
        explicit JumpCharacter(SpriteAnimData animData, float distance, float risingTime, float vX) :
                animData(std::move(animData)), started(false), vX(vX),
                elapsedTime(0), longJump(true) {}

        SpriteAnimData animData;
        Uint32 startTime; // seconds
        float elapsedTime;  // seconds
        float vX;
        float vY;
        bool longJump;
        bool started;

        REFLECT()
    };
}

#endif //INANNA_JUMPCHARACTER_H
