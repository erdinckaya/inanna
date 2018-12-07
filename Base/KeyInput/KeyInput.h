//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_KEYINPUT_H
#define INANNA_KEYINPUT_H


#include <SDL_scancode.h>
#include <SDL_events.h>
#include <map>

namespace Inanna {

    class KeyInput {
    public:
        void BeginNewFrame();

        void KeyUpEvent(SDL_Event &event);

        void KeyDownEvent(SDL_Event &event);

        bool WasKeyPressed(SDL_Scancode key);

        bool WasKeyReleased(SDL_Scancode key);

        bool IsKeyHeld(SDL_Scancode key);

        void PrintKeys();

    private:
        std::map<SDL_Scancode, bool> heldKeys;
        std::map<SDL_Scancode, bool> pressedKeys;
        std::map<SDL_Scancode, bool> releasedKeys;
    };
}

#endif //INANNA_KEYINPUT_H
