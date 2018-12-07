//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_BUTTONSYSTEM_H
#define INANNA_BUTTONSYSTEM_H

#include <entityx/System.h>
#include <entityx/Entity.h>
#include "../Widgets/Button.h"

namespace Inanna {

    class ButtonSystem : public entityx::System<ButtonSystem> {
    public:
        explicit ButtonSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Button, Widget>([this](entityx::Entity entity, Button &button, Widget &widget) {
                bool isOver = widget.mouseWidget;
//                bool isMouseDown = World::InputMouse.WasPressed(MouseButtonState::MouseLeftDown);
            });
        }
    };
}
#endif //INANNA_BUTTONSYSTEM_H
