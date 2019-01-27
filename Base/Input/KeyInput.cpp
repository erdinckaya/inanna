//
// Created by Erdınc Kaya on 2018-12-07.
//

#include "KeyInput.h"
#include "../UI/WindowManager.h"
#include "../Game/Components/UserKey.h"

Inanna::KeyInput Inanna::KeyInput::Instance;

Inanna::KeyInput::KeyInput() : KEY_DOWN_LIMIT(2) {}

void Inanna::KeyInput::BeginNewFrame() {
    pressedKeys.clear();
    releasedKeys.clear();
}

void Inanna::KeyInput::KeyDownEvent(SDL_Event &event) {
    pressedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = true;

    firstDownKeys[event.key.keysym.scancode]++;
    if (firstDownKeys[event.key.keysym.scancode] >= KEY_DOWN_LIMIT) {
        firstDownKeys[event.key.keysym.scancode] = KEY_DOWN_LIMIT;
    } else if (firstDownKeys[event.key.keysym.scancode] == 1) {
        WindowManager::spriteAnimationFactory.entities.create().assign<UserKey>(event.key.keysym.scancode,
                                                                                event.key.timestamp,
                                                                                true);
    }
}

void Inanna::KeyInput::KeyUpEvent(SDL_Event &event) {
    releasedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = false;
    firstDownKeys[event.key.keysym.scancode] = 0;

    WindowManager::spriteAnimationFactory.entities.create().assign<UserKey>(event.key.keysym.scancode,
                                                                            event.key.timestamp,
                                                                            false);
}

bool Inanna::KeyInput::WasKeyPressed(SDL_Scancode key) {
    return pressedKeys[key];
}

bool Inanna::KeyInput::WasKeyReleased(SDL_Scancode key) {
    return releasedKeys[key];
}

bool Inanna::KeyInput::IsKeyHit(SDL_Scancode key) {
    return firstDownKeys[key] == 1;
}

bool Inanna::KeyInput::IsKeyHeld(SDL_Scancode key) {
    return heldKeys[key];
}

void Inanna::KeyInput::PrintKeys() {
    printf("=================START================\n");
    for (auto &pressedKey : pressedKeys) {
        printf("Pressed Key %d state %d\n", (int) pressedKey.first, (int) pressedKey.second);
    }

    for (auto &heldKey : heldKeys) {
        printf("Held Key %d state %d\n", (int) heldKey.first, (int) heldKey.second);
    }

    for (auto &releasedKey : releasedKeys) {
        printf("Released Key %d state %d\n", (int) releasedKey.first, (int) releasedKey.second);
    }

    for (auto &hitKey : firstDownKeys) {
        printf("Hit Key %d state %d\n", (int) hitKey.first, (int) hitKey.second);
    }
    printf("=================END==================\n");

}
