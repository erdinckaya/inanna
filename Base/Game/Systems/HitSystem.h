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
#include "../Command/Components/DamageReceiveCommand.h"

namespace Inanna {
    struct HitSystem : public entityx::System<HitSystem>, entityx::Receiver<HitSystem> {
        explicit HitSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
            events.subscribe<AbortEvent>(*this);
        }

        void CheckDamage(entityx::EntityManager &entities, std::vector<entityx::Entity> &hits) {
            entities.each<Character, SpriteAnimation, Position, Facing>(
                    [this, &hits, &entities](entityx::Entity entity, Character &character, SpriteAnimation &animation,
                            Position &position, Facing facing) {
                        if (!entity.has_component<Hit>()) {
                            auto animSize = animation.Size();
                            auto boundBox = Rectf(position.global, animSize);


                            const int size = static_cast<const int>(hits.size());
                            for (int i = 0; i < size; ++i) {
                                auto ent = hits[i];
                                auto anim = ent.component<SpriteAnimation>();
                                auto keyFrame = anim->KeyFrame();
                                if (anim->hitbox != Rectf(0, 0, 0, 0)) {
                                    if (boundBox.IsIntersect(anim->hitbox)) {
                                        entities.create().assign<DamageReceiveCommand>(ent, entity, 5);
                                    }
                                }
                            }
                        }
                    });
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<entityx::Entity> hits;
            entities.each<Character, SpriteAnimation, Hit>(
                    [this, dt, &hits](entityx::Entity entity, Character &character, SpriteAnimation &anim, Hit &hit) {
                        INANNA_REMOVE_COMPONENT(entity, MoveCharacter)
                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, hit.animData)
                        entity.component<SpriteAnimation>()->stayAtLastFrame = hit.stayAtLastFrame;
                        hits.push_back(entity);
                    });
            CheckDamage(entities, hits);

        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<Hit>()) {
                manager->emit<HitEnd>(event.entity);
            }
        }

        void receive(const AbortEvent &abortEvent) {
            AbortEvent event = abortEvent;
            if (event.entity.has_component<Hit>() && abortEvent.level > 0) {
                manager->emit<HitEnd>(event.entity);
            }
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_HITSYSTEM_H
