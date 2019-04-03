//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_KEYINPUT_H
#define INANNA_KEYINPUT_H


#include <SDL_scancode.h>
#include <SDL_events.h>
#include <map>
#include "../Game/Util/GameKey.h"

namespace Inanna {

    class KeyInput {
    public:
        KeyInput();

        void BeginNewFrame();

        void KeyUpEvent(SDL_Event &event);

        void KeyDownEvent(SDL_Event &event);

        bool WasKeyPressed(SDL_Scancode key);

        bool WasKeyReleased(SDL_Scancode key);

        bool IsKeyHit(SDL_Scancode key);

        bool IsKeyHeld(SDL_Scancode key);

        bool IsKeyHeld(GameKey key);

        bool WasKeyReleased(GameKey key);

        void PrintKeys();

        static KeyInput Instance;

        std::map<SDL_Scancode, bool> heldKeys;
        std::map<SDL_Scancode, int> firstDownKeys;
        std::map<SDL_Scancode, bool> pressedKeys;
        std::map<SDL_Scancode, bool> releasedKeys;

        const int KEY_DOWN_LIMIT;
    };
}

#endif //INANNA_KEYINPUT_H
