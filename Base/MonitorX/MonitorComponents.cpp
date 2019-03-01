//
// Created by Erdınc Kaya on 2019-01-04.
//

#include "../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

#include "../UI/Components/Renderable.h"
#include "../UI/Components/Position.h"
#include "../Game/Components/Facing.h"
#include "../SpriteAnimation/Components/SpriteAnimation.h"
#include "../SpriteAnimation/Components/SpriteLoop.h"
#include "../Game/Components/MoveCharacter.h"
#include "../Game/Components/Roll.h"
#include "../Game/Components/Oryu.h"
#include "../Game/Components/Run.h"
#include "../Game/Components/JumpCharacter.h"
#include "../Game/Components/JumpState.h"
#include "../Game/Components/MoveState.h"
#include "../Game/Components/CrouchState.h"
#include "../Game/Components/Character.h"
#include "../Game/Components/Crouch.h"
#include "../Game/Components/UserKeyHistory.h"

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
                    REFLECT_STRUCT_MEMBER(stayAtLastFrame)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::SpriteLoop)
                    REFLECT_STRUCT_MEMBER(start)
                    REFLECT_STRUCT_MEMBER(end)
REFLECT_STRUCT_END()


REFLECT_STRUCT_BEGIN(Inanna::Facing)
                    REFLECT_STRUCT_MEMBER(left)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::MoveCharacter)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(direction)
                    REFLECT_STRUCT_MEMBER(speed)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::Roll)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(direction)
                    REFLECT_STRUCT_MEMBER(speed)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::Oryu)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(direction)
                    REFLECT_STRUCT_MEMBER(speed)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::Run)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(direction)
                    REFLECT_STRUCT_MEMBER(speed)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::JumpCharacter)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(direction)
                    REFLECT_STRUCT_MEMBER(speed)

REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::Crouch)
                    REFLECT_STRUCT_MEMBER(down)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::JumpState)
                    REFLECT_STRUCT_MEMBER(lock)
                    REFLECT_STRUCT_MEMBER(state)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::MoveState)
                    REFLECT_STRUCT_MEMBER(lock)
                    REFLECT_STRUCT_MEMBER(state)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::CrouchState)
                    REFLECT_STRUCT_MEMBER(lock)
                    REFLECT_STRUCT_MEMBER(state)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(Inanna::UserKey)
                    REFLECT_STRUCT_MEMBER(key)
                    REFLECT_STRUCT_MEMBER(time)
                    REFLECT_STRUCT_MEMBER(down)
REFLECT_STRUCT_END()


REFLECT_STRUCT_BEGIN(Inanna::UserKeyHistory)
                    REFLECT_STRUCT_MEMBER(buffer)
REFLECT_STRUCT_END()