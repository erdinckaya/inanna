//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_BUTTON_H
#define INANNA_BUTTON_H

#include "../Types.h"
#include "../../../Assets/Resources.h"

namespace Inanna {
    struct Button {
    public:
        explicit Button() {
            isActive = true;
            for (auto &state : states) {
                state = ImageAsset();
            }
        };



        Button* SetStateAsset(const ButtonState &state, const ImageAsset asset) {
            states[state] = asset;
            return this;
        }

        ImageAsset GetStateAsset(const ButtonState &state) {
            return states[state];
        }

        void SetActive(bool value) {
            isActive = value;
        }

        bool GetActive() {
            return isActive;
        }

    private:
        bool isActive;
        ImageAsset states[ButtonState::Count];
    };
}
#endif //INANNA_BUTTON_H
