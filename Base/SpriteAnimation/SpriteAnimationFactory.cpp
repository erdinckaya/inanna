//
// Created by Erdınc Kaya on 2019-01-18.
//

#include "SpriteAnimationFactory.h"
#include "Components/SpriteAnimation.h"
#include "../UI/Components/Position.h"
#include "../UI/Components/Scalable.h"

entityx::Entity Inanna::SpriteAnimationFactory::CreateAnimation(const SpriteAnimData &animation) {
    auto entity = entities.create();
    auto comp = entity.assign<SpriteAnimation>(animation);
    comp->loop = true;
    entity.assign<Position>(Vecf(100, 100));
    return entity;
}
