//
// Created by misterdortnal on 20.11.2018.
//

#ifndef INANNA_GAMECONNECTIONCONFIG_H
#define INANNA_GAMECONNECTIONCONFIG_H


#include <yojimbo.h>
#include <shared.h>
#include "GameChannel.h"

// the client and server config
struct GameConnectionConfig : public yojimbo::ClientServerConfig {
    GameConnectionConfig() {
        protocolId = ProtocolId;
        numChannels = 2;
        channel[(int) GameChannel::RELIABLE].type = yojimbo::CHANNEL_TYPE_RELIABLE_ORDERED;
        channel[(int) GameChannel::UNRELIABLE].type = yojimbo::CHANNEL_TYPE_UNRELIABLE_UNORDERED;
    }
};


#endif //INANNA_GAMECONNECTIONCONFIG_H
