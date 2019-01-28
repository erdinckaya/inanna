//
// Created by Erdınc Kaya on 2019-01-04.
//

#include "../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

#include "../UI/Components/Renderable.h"
#include "../UI/Components/Position.h"
#include "../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Game/Components/MoveCharacter.h"
#include "../Game/Components/Character.h"

REFLECT_STRUCT_BEGIN(Inanna::Renderable)
                    REFLECT_STRUCT_MEMBER(rotation)
                    REFLECT_STRUCT_MEMBER(hasFrame)
                    REFLECT_STRUCT_MEMBER(pos)
                    REFLECT_STRUCT_MEMBER(target)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(ImageAsset)
                    REFLECT_STRUCT_MEMBER(name)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::Position)
                    REFLECT_STRUCT_MEMBER(position)
                    REFLECT_STRUCT_MEMBER(global)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::SpriteAnimation)
                    REFLECT_STRUCT_MEMBER(animData)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(frameIndex)
                    REFLECT_STRUCT_MEMBER(loop)
                    REFLECT_STRUCT_MEMBER(pingpong)
                    REFLECT_STRUCT_MEMBER(killAtFinish)
                    REFLECT_STRUCT_MEMBER(reverse)
                    REFLECT_STRUCT_MEMBER(state)
REFLECT_STRUCT_END()


REFLECT_STRUCT_BEGIN(Inanna::MoveCharacter)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(direction)
                    REFLECT_STRUCT_MEMBER(speed)

REFLECT_STRUCT_END()

