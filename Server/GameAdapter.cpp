//
// Created by misterdortnal on 20.11.2018.
//


#include "GameAdapter.h"
#include "GameServer.h"

void GameAdapter::OnServerClientConnected(int clientIndex) {
    if (server != nullptr) {
        server->ClientConnected(clientIndex);
    }
}

void GameAdapter::OnServerClientDisconnected(int clientIndex) {
    if (server != nullptr) {
        server->ClientDisconnected(clientIndex);
    }
}
