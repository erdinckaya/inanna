//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_SPRITEMACRO_H
#define INANNA_SPRITEMACRO_H

#include "../Game/Command/Components/CommandLink.h"

#define INANNA_REPLACE_SPRITE_ANIM(entity, anim) \
    entity.remove<SpriteAnimation>(); \
    entity.assign<SpriteAnimation>(anim); \

#define INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(entity, anim) \
    entity.remove<SpriteAnimation>(); \
    auto comp = entity.assign<SpriteAnimation>(anim); \
    comp->loop = true; \

#define INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, anim) \
    if (entity.has_component<SpriteAnimation>()) { \
        if (entity.component<SpriteAnimation>()->animData != anim) { \
            entity.remove<SpriteAnimation>(); \
            entity.assign<SpriteAnimation>(anim); \
        } \
    } \

#define INANNA_REPLACE_SPRITE_ANIM_IF_NOT_LOOP(entity, anim) \
    if (entity.has_component<SpriteAnimation>()) { \
        if (entity.component<SpriteAnimation>()->animData != anim) { \
            entity.remove<SpriteAnimation>(); \
            entity.assign<SpriteAnimation>(anim)->loop = true; \
        } \
    } \

#define INANNA_REMOVE_COMPONENT(entity, comp) \
    if (entity.has_component<comp>()) { \
        entity.remove<comp>(); \
    } \

#define INANNA_COMMAND_EXECUTED(entity) \
    if (entity.has_component<CommandLink>()) { \
        auto link = entity.component<CommandLink>(); \
        auto ent = link->entity; \
        link->onExecuted(ent); \
    } \

#endif //INANNA_SPRITEMACRO_H
