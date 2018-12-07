//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_BUTTONSYSTEM_H
#define INANNA_BUTTONSYSTEM_H

#include <entityx/System.h>
#include <entityx/Entity.h>
#include "../Widgets/Button.h"
#include "../../Input/MouseInput.h"

namespace Inanna {

    class ButtonSystem : public entityx::System<ButtonSystem> {
    public:
        explicit ButtonSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Button, Widget, Renderable>(
                    [this](entityx::Entity entity, Button &button, Widget &widget, Renderable &renderable) {
                        bool isOver = widget.mouseWidget;
                        bool isHolding = MouseInput::Instance.IsMouseHeld(MouseButtonState::MouseLeft) ||
                                           MouseInput::Instance.IsMouseHeld(MouseButtonState::Finger);
                        if (button.GetActive()) {
                            if (isOver) {
                                if (isHolding) {
                                    renderable.target = button.GetStateAsset(ButtonState::Pressed);
                                } else {
                                    renderable.target = button.GetStateAsset(ButtonState::Over);
                                }
                            } else {
                                renderable.target = button.GetStateAsset(ButtonState::Idle);
                            }
                        } else {
                            renderable.target = button.GetStateAsset(ButtonState::Disable);
                        }
                    });
        }
    };
}
#endif //INANNA_BUTTONSYSTEM_H
