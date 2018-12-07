//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_MOUSEINPUT_H
#define INANNA_MOUSEINPUT_H


#include <map>
#include "../UI/Types.h"

namespace Inanna {

    class MouseInput {
    public:
        void BeginNewFrame();

        void MouseUpEvent(const SDL_Event &event);

        void MouseDownEvent(const SDL_Event &event);

        bool WasMousePressed(const MouseButtonState &key);

        bool WasMouseReleased(const MouseButtonState &key);

        bool IsMouseHeld(const MouseButtonState &key);

        void PrintKeys();

        static MouseInput Instance;

    private:
        MouseButtonState GetState(const SDL_Event &event) const;

        std::map<MouseButtonState, bool> heldKeys;
        std::map<MouseButtonState, bool> pressedKeys;
        std::map<MouseButtonState, bool> releasedKeys;
    };
}

#endif //INANNA_MOUSEINPUT_H
