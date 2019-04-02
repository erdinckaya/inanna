//
// Created by misterdortnal on 02.04.2019.
//

#ifndef INANNA_DAMAGESYSTEM_H
#define INANNA_DAMAGESYSTEM_H

#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../../SpriteAnimation/Event/SpriteIndex.h"
#include "../../SpriteAnimation/Event/SpriteAnimEnd.h"
#include "../Util/Chrono.h"
#include "../Components/Oryu.h"
#include "../Events/OryuEnd.h"
#include "../Components/Damage.h"
#include "../Components/Health.h"
#include "../Events/DamageEnd.h"
#include "../Events/AbortEvent.h"

namespace Inanna {
    struct DamageSystem : public entityx::System<DamageSystem>, entityx::Receiver<DamageSystem> {

        explicit DamageSystem() = default;

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Damage, Health>(
                    [this](entityx::Entity entity, Character &character, Damage &damage, Health &health) {
                        health.health -= damage.damage;
                        manager->emit<AbortEvent>(entity, 2);
                        if (health.health < 0) {
                            health.health = 0;
                        }
                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, damage.animData)
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<Damage>()) {
                manager->emit<DamageEnd>(event.entity);
            }
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_DAMAGESYSTEM_H
