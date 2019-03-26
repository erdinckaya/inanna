//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HITSYSTEM_H
#define INANNA_HITSYSTEM_H


#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../Components/Hit.h"

namespace Inanna {
    struct HitSystem : public entityx::System<HitSystem>, entityx::Receiver<HitSystem> {
        explicit HitSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, SpriteAnimation, Hit>(
                    [this, dt](entityx::Entity entity, Character &character, SpriteAnimation &anim, Hit &hit) {
                        INANNA_REMOVE_COMPONENT(entity, MoveCharacter)
                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, hit.animData);
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<Hit>()) {
                manager->emit<HitEnd>(event.entity);
            }
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_HITSYSTEM_H
