#include <iostream>
#include "Assets/Resources.h"
#include "Server/GameServer.h"

#include <entityx/entityx.h>
#include <yojimbo.h>
#include <thread>
#include <shared.h>

void startServer() {
    printf("\n");

    if (!InitializeYojimbo()) {
        printf("error: failed to initialize Yojimbo!\n");
        return;
    }

    yojimbo_log_level(YOJIMBO_LOG_LEVEL_INFO);

    srand((unsigned int) time(nullptr));

    printf("started server on port %d (secure)\n", ServerPort);

    GameServer server(Address("127.0.0.1", ServerPort));
    server.Run();

    ShutdownYojimbo();

    printf("\n");

    server.Run();
}

int main() {

    printf("Piece id %s parent %s\n", Resources::PIECES.CYAN.id, Resources::PIECES.CYAN.parent);
    auto server = std::make_unique<std::thread>(std::thread(startServer));
    server->join();
    return 0;
}