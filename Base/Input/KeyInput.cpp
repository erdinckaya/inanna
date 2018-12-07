//
// Created by Erdınc Kaya on 2018-12-07.
//

#include "KeyInput.h"

Inanna::KeyInput Inanna::KeyInput::Instance;

void Inanna::KeyInput::BeginNewFrame() {
    pressedKeys.clear();
    releasedKeys.clear();
}

void Inanna::KeyInput::KeyDownEvent(SDL_Event &event) {
    pressedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = true;
}

void Inanna::KeyInput::KeyUpEvent(SDL_Event &event) {
    releasedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = false;
}

bool Inanna::KeyInput::WasKeyPressed(SDL_Scancode key) {
    return pressedKeys[key];
}

bool Inanna::KeyInput::WasKeyReleased(SDL_Scancode key) {
    return releasedKeys[key];
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
    printf("=================END==================\n");

}
