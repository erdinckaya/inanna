//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_GAMEKEY_H
#define INANNA_GAMEKEY_H

#include "../../../ThirdParty/enum.h"

namespace Inanna {
//    enum GameKey {
//        InValid = -1,
//        Back_GK = 0,
//        Jump_GK = 1,
//        Forward_GK = 2,
//        Crouch_GK = 3,
//        LittleFist_GK = 4,
//        LittleKick_GK = 5,
//        BigFist_GK = 5,
//        BigKick_GK = 7,
//
//        NumOfGameKey = 8
//    };

    BETTER_ENUM(GameKey, int, InValid = -1, Back = 0, Jump = 1, Forward = 2, Crouch = 3, LittleFist = 4, LittleKick = 5, BigKick = 7)

}



#endif //INANNA_GAMEKEY_H
