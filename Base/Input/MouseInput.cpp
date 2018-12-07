//
// Created by Erdınc Kaya on 2018-12-07.
//

#include "MouseInput.h"

Inanna::MouseInput Inanna::MouseInput::Instance;

void Inanna::MouseInput::BeginNewFrame() {
    pressedKeys.clear();
    releasedKeys.clear();
}

void Inanna::MouseInput::MouseDownEvent(const SDL_Event &event) {
    Inanna::MouseButtonState state = GetState(event);

    pressedKeys[state] = true;
    heldKeys[state] = true;
}

void Inanna::MouseInput::MouseUpEvent(const SDL_Event &event) {
    Inanna::MouseButtonState state = GetState(event);

    releasedKeys[state] = true;
    heldKeys[state] = false;
}

bool Inanna::MouseInput::WasMousePressed(const Inanna::MouseButtonState &key) {
    return pressedKeys[key];
}

bool Inanna::MouseInput::WasMouseReleased(const Inanna::MouseButtonState &key) {
    return releasedKeys[key];
}

bool Inanna::MouseInput::IsMouseHeld(const Inanna::MouseButtonState &key) {
    return heldKeys[key];
}

void Inanna::MouseInput::PrintKeys() {
    printf("=================START================\n");
    for (auto &pressedKey : pressedKeys) {
        printf("Pressed Mouse Key %d state %d\n", (int) pressedKey.first, (int) pressedKey.second);
    }

    for (auto &heldKey : heldKeys) {
        printf("Held Mouse Key %d state %d\n", (int) heldKey.first, (int) heldKey.second);
    }

    for (auto &releasedKey : releasedKeys) {
        printf("Released Mouse Key %d state %d\n", (int) releasedKey.first, (int) releasedKey.second);
    }
    printf("=================END==================\n");
}



Inanna::MouseButtonState Inanna::MouseInput::GetState(const SDL_Event &event) const {
    Inanna::MouseButtonState state = Inanna::Finger;
    switch (event.type) {
        case SDL_FINGERUP:
        case SDL_FINGERDOWN: {
            state = Inanna::Finger;
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            if (event.button.button == SDL_BUTTON_LEFT) {
                state = Inanna::MouseLeft;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                state = Inanna::MouseRight;
            } else if (event.button.button == SDL_BUTTON_MIDDLE){
                state = Inanna::MouseMiddle;
            }
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            if (event.button.button == SDL_BUTTON_LEFT) {
                state = Inanna::MouseLeft;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                state = Inanna::MouseRight;
            } else if (event.button.button == SDL_BUTTON_MIDDLE){
                state = Inanna::MouseMiddle;
            }
            break;
        }
    }
    return state;
}