//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_SPRITEMACRO_H
#define INANNA_SPRITEMACRO_H

#define INANNA_REPLACE_SPRITE_ANIM(entity, anim) \
    entity.remove<SpriteAnimation>(); \
    entity.assign<SpriteAnimation>(anim); \

#define INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, anim) \
    if (entity.has_component<SpriteAnimation>()) { \
        if (entity.component<SpriteAnimation>()->animData != anim) { \
            entity.remove<SpriteAnimation>(); \
            entity.assign<SpriteAnimation>(anim); \
        } \
    } \

#define INANNA_REMOVE_COMPONENT(entity, comp) \
    if (entity.has_component<comp>()) { \
        entity.remove<comp>(); \
    } \



#endif //INANNA_SPRITEMACRO_H
