//
// Created by misterdortnal on 20.11.2018.
//

#ifndef INANNA_GAMEADAPTER_H
#define INANNA_GAMEADAPTER_H


#include <yojimbo.h>
#include "GameMessageFactory.h"

class GameServer;

class GameAdapter : public yojimbo::Adapter {
public:
    explicit GameAdapter(GameServer *server = nullptr) {
        this->server = server;
    }

    yojimbo::MessageFactory *CreateMessageFactory(yojimbo::Allocator &allocator) override {
        return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
    }

    void OnServerClientConnected(int clientIndex) override;

    void OnServerClientDisconnected(int clientIndex) override;

private:
    GameServer *server;
};

#endif //INANNA_GAMEADAPTER_H
