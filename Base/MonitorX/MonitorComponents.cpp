//
// Created by Erdınc Kaya on 2019-01-04.
//

#include "../../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

#include "../UI/Components/Renderable.h"
#include "../UI/Components/Position.h"

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
