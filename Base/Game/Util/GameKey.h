//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_GAMEKEY_H
#define INANNA_GAMEKEY_H

#include "../../../ThirdParty/enum.h"

namespace Inanna {
    BETTER_ENUM(GameKey, int, InValid = -1, Back = 1, Up = 2, Forward = 4, Down = 8, LittleFist = 16, LittleKick = 32,
                BigFist = 64, BigKick = 128, Hit = (16 | 32 | 64 | 128))

#define IS_HIT(game_key) ((GameKey::Hit & game_key) != 0)
}


#endif //INANNA_GAMEKEY_H
