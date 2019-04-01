//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUNSYSTEM_H
#define INANNA_RUNSYSTEM_H

#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../../SpriteAnimation/Event/SpriteAnimEnd.h"
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Event/SpriteIndex.h"
#include "../Components/Run.h"
#include "../Events/RunEnd.h"

namespace Inanna {
    struct RunSystem : public entityx::System<RunSystem>, entityx::Receiver<RunSystem> {
        explicit RunSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, Run>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, Run &run) {
                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT_LOOP(entity, run.animData);

                        double speed = 1000.0 / run.speed;
                        if (run.time >= speed) {
                            run.time = 0;
                        } else {
                            run.time += dt;
                        }
                        position.position += run.direction * run.speed;
                    });
        }

    };
}

#endif //INANNA_RUNSYSTEM_H
