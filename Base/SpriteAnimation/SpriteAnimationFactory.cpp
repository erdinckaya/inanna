//
// Created by Erdınc Kaya on 2019-01-18.
//

#include "SpriteAnimationFactory.h"
#include "Components/SpriteAnimation.h"

entityx::Entity Inanna::SpriteAnimationFactory::CreateAnimation(const SpriteAnimData &animation) {
    auto entity = entities.create();
    auto comp = entity.assign<SpriteAnimation>(animation);
    return entity;
}
