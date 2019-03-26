//
// Created by Erdınc Kaya on 2019-03-13.
//

#ifndef INANNA_CHARACTERBEHAIVOUR_H
#define INANNA_CHARACTERBEHAIVOUR_H

#include "../../../ThirdParty/enum.h"
#include "../../../ThirdParty/boolinq.h"
#include <SDL_types.h>
#include <entityx/Entity.h>
#include "../Components/CharacterState.h"
#include "../../Input/KeyInput.h"


using namespace boolinq;

namespace Inanna {
    BETTER_ENUM(CharacterBehaviour, Uint8, Idle = 0, MoveLeft = 1, MoveRight = 2, Jump = 3, Crouch = 4, JumpLeft = 5,
                JumpRight = 6, Run = 7, JumpBack = 8, Oryu = 9, LittleFist = 10, LittleKick = 11, BigFist = 12, BigKick = 13,
                CrouchLittleFist = 14, CrouchLittleKick = 15, CrouchBigFist = 16, CrouchBigKick = 17,
                JumpLittleFist = 18, JumpLittleKick = 19, JumpBigFist = 20, JumpBigKick = 21)

    struct CharacterBehaviourUtil {
        static CharacterBehaviour GetCharacterBehaviour(entityx::Entity entity) {
            auto keys = from(KeyInput::Instance.heldKeys).where(
                    [](const std::pair<SDL_Scancode, bool> &p) { return p.second; }).
                    select([](const std::pair<SDL_Scancode, bool> p) { return p.first; }).toVector();
            const int size = static_cast<const int>(keys.size());
            if (size == 1) {
                auto key = keys[0];
                switch (key) {
                    case SDL_SCANCODE_LEFT: {
                        return CharacterBehaviour::MoveLeft;
                    }
                    case SDL_SCANCODE_RIGHT: {
                        return CharacterBehaviour::MoveRight;
                    }
                    case SDL_SCANCODE_UP: {
                        return CharacterBehaviour::Jump;
                    }
                    case SDL_SCANCODE_DOWN: {
                        return CharacterBehaviour::Crouch;
                    }
                    default:
                        break;
                }
            } else if (size == 2) {
                auto first = keys[0];
                auto second = keys[1];

                if (first == SDL_SCANCODE_DOWN) {
                    if (second != SDL_SCANCODE_UP) {
                        return CharacterBehaviour::Crouch;
                    }
                }

                if (second == SDL_SCANCODE_DOWN) {
                    if (first != SDL_SCANCODE_UP) {
                        return CharacterBehaviour::Crouch;
                    }
                }

                if (first == SDL_SCANCODE_UP) {
                    if (second == SDL_SCANCODE_LEFT) {
                        return CharacterBehaviour::JumpLeft;
                    } else if (second == SDL_SCANCODE_RIGHT) {
                        return CharacterBehaviour::JumpRight;
                    }
                }

                if (second == SDL_SCANCODE_UP) {
                    if (first == SDL_SCANCODE_LEFT) {
                        return CharacterBehaviour::JumpLeft;
                    } else if (first == SDL_SCANCODE_RIGHT) {
                        return CharacterBehaviour::JumpRight;
                    }
                }
            }

            return CharacterBehaviour::Idle;
        }
    };
}

#endif //INANNA_CHARACTERBEHAIVOUR_H
