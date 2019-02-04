//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_GAMEKEY_H
#define INANNA_GAMEKEY_H

#include "../../../ThirdParty/enum.h"

namespace Inanna {
    BETTER_ENUM(GameKey, int, InValid = -1, Back = 0, Jump = 1, Forward = 2, Crouch = 3, LittleFist = 4, LittleKick = 5,
                BigFist = 6, BigKick = 7, Hit = 8)

}


#endif //INANNA_GAMEKEY_H
