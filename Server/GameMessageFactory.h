//
// Created by misterdortnal on 20.11.2018.
//

#ifndef INANNA_GAMEMESSAGEFACTORY_H
#define INANNA_GAMEMESSAGEFACTORY_H


#include "GameMessageType.h"
#include "MyMessage.h"

YOJIMBO_MESSAGE_FACTORY_START(GameMessageFactory, (int) GameMessageType::COUNT) ;
            YOJIMBO_DECLARE_MESSAGE_TYPE((int) GameMessageType::TEST, MyMessage);
YOJIMBO_MESSAGE_FACTORY_FINISH();

#endif //INANNA_GAMEMESSAGEFACTORY_H
