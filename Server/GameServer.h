//
// Created by misterdortnal on 20.11.2018.
//

#ifndef INANNA_GAMESERVER_H
#define INANNA_GAMESERVER_H


#include <yojimbo.h>
#include "GameAdapter.h"
#include "GameConnectionConfig.h"

class GameServer {

public:
    explicit GameServer(const yojimbo::Address &address);

    void ClientConnected(int clientIndex);

    void ClientDisconnected(int clientIndex);

    void Run();

private:
    float time;
    bool running;

    GameAdapter adapter;
    GameConnectionConfig connectionConfig;
    yojimbo::Server server;

    void Update(float dt);

    void ProcessMessages();

    void ProcessMessage(int clientIndex, int channelIndex, yojimbo::Message *message);

    void ProcessTestMessage(int clientIndex, int channelIndex, MyMessage *message);
};

#endif //INANNA_GAMESERVER_H
