//
// Created by misterdortnal on 20.11.2018.
//

#include "GameServer.h"

#include "GameServer.h"
#include <iostream>
#include <string>
#include "shared.h"

uint8_t DEFAULT_PRIVATE_KEY[KeyBytes] = {0x60, 0x6a, 0xbe, 0x6e, 0xc9, 0x19, 0x10, 0xea,
                                         0x9a, 0x65, 0x62, 0xf6, 0x6f, 0x2b, 0x30, 0xe4,
                                         0x43, 0x71, 0xd6, 0x2c, 0xd1, 0x99, 0x27, 0x26,
                                         0x6b, 0x3c, 0x60, 0xf4, 0xb7, 0x15, 0xab, 0xa1};
static const int MAX_PLAYERS = 8;


GameServer::GameServer(const yojimbo::Address &address) :
        time(0.0f),
        running(true),
        adapter(this),
        server(yojimbo::GetDefaultAllocator(), DEFAULT_PRIVATE_KEY, address, connectionConfig, adapter, time) {
    // start the server
    server.Start(MAX_PLAYERS);
    if (!server.IsRunning()) {
        throw std::runtime_error("Could not start server at port " + std::to_string(address.GetPort()));
    }

    // print the port we got in case we used port 0
    char addressString[256];
    server.GetAddress().ToString(addressString, sizeof(addressString));
    printf("server address is %s\n", addressString);

    // ... load game ...
}

void GameServer::ClientConnected(int clientIndex) {
    std::cout << "client " << clientIndex << " connected" << std::endl;
}

void GameServer::ClientDisconnected(int clientIndex) {
    std::cout << "client " << clientIndex << " disconnected" << std::endl;
}

void GameServer::Run() {
    float fixedDt = 1.0f / 10.0f;
    while (running) {
        double currentTime = yojimbo_time();
        if (time <= currentTime) {
            Update(fixedDt);
            time += fixedDt;
        } else {
            yojimbo_sleep(time - currentTime);
        }
    }
}

void GameServer::Update(float dt) {
// stop if server is not running
    if (!server.IsRunning()) {
        running = false;
        return;
    }

    server.AdvanceTime(time);
    server.ReceivePackets();
    // update server and process messages


    // ... process client inputs ...
    // ... update game ...
    // ... send game state to clients ...

    ProcessMessages();

    server.SendPackets();

}

void GameServer::ProcessMessages() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (server.IsClientConnected(i)) {
            for (int j = 0; j < connectionConfig.numChannels; j++) {
                yojimbo::Message *message = server.ReceiveMessage(i, j);
                while (message != nullptr) {
                    ProcessMessage(i, j, message);
                    server.ReleaseMessage(i, message);
                    message = server.ReceiveMessage(i, j);
                }
            }
        }
    }
}

void GameServer::ProcessMessage(int clientIndex, int channelIndex, yojimbo::Message *message) {
    switch (message->GetType()) {
        case (int) GameMessageType::TEST:
            ProcessTestMessage(clientIndex, channelIndex, (MyMessage *) message);
            break;
        default:
            break;
    }
}

void GameServer::ProcessTestMessage(int clientIndex, int channelIndex, MyMessage *message) {
    printf("Client index %d sent message %s\n", clientIndex, message->text);

    auto respond = (MyMessage *) server.CreateMessage(clientIndex, (int) GameMessageType::TEST);
    respond->m_data = 100;
    strcpy(respond->text, "BEYAZ!");

    server.SendMessage(clientIndex, channelIndex, respond);
}

