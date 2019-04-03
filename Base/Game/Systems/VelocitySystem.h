//
// Created by Erdınc Kaya on 2019-04-03.
//

#ifndef INANNA_VELOCITYSYSTEM_H
#define INANNA_VELOCITYSYSTEM_H

#include <entityx/System.h>
#include "../Components/Velocity.h"
#include "../../UI/Components/Position.h"

#include "../../Util/Math/Physics.h"

namespace Inanna {
    struct VelocitySystem : entityx::System<VelocitySystem> {

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Velocity, Position>(
                    [this, dt](entityx::Entity entity, Velocity &velocity, Position &position) {
                        auto t = static_cast<float>(dt * 0.01f);
                        float x = t * velocity.value.x;
                        float vy = velocity.value.y;
                        if (t == 0) {
                            printf("12312312\n");
                        }
                        float y = Physics::Delta(vy, static_cast<const float &>(t), Physics::GRAVITY);
                        velocity.value = Vecf(velocity.value.x, vy);

                        position.position += Vecf(x, y);

                        if (position.position.y < FLOOR) {
                            velocity.value = Vecf(velocity.value.x, 0);
                            position.position = Vecf(position.position.x, FLOOR);
                        }
                    });
        }

    private:
        static constexpr float FLOOR = 100;
    };
}

#endif //INANNA_VELOCITYSYSTEM_H
