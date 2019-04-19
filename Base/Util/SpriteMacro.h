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
            entity.replace<SpriteAnimation>(anim); \
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



#define HAS_COMP(e, C) ((e).has_component<C>())

#define COMP(e, C) ((e).component<C>())

#define IS_PUSHING(e) (HAS_COMP(e, MoveCharacter) || HAS_COMP(e, JumpCharacter) || HAS_COMP(e, Run) || HAS_COMP(e, JumpBack))


#define FOR_I(C) \
const int size = static_cast<const int>(C.size());\
for (int i = 0; i < size; ++i) \

#define FOR_IJ(C, J) \
const int size_J = static_cast<const int>(C.size());\
for (int J = 0; J < size_J; ++J) \

#define FOR_R(C) \
const int size = static_cast<const int>(C.size());\
for (int i = size - 1; i > -1; --i) \

#define FOR_E(C, elem) \
for (auto& elem : C) \

#define HAS_KEY(m, k) ((m).find((k)) != (m).end())


#endif //INANNA_SPRITEMACRO_H
