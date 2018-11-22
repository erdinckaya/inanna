//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_CHILDINPUTSYSTEM_H
#define INANNA_CHILDINPUTSYSTEM_H

#include <entityx/System.h>
#include "../Components/ChildInput.h"
namespace Inanna {

    class ChildInputSystem : public entityx::System<ChildInputSystem> {
    public:
        explicit ChildInputSystem() = default;

        void AddChild(ChildInput &input) {
            auto parentWidget = input.parent->component<Widget>();
            auto childWidget = input.child->component<Widget>();
            parentWidget->AddChild(input.child);
            childWidget->SetParent(input.parent);
        }

        void RemoveChild(ChildInput &input) {
            auto parentWidget = input.parent->component<Widget>();
            auto childWidget = input.child->component<Widget>();
            parentWidget->RemoveChild(input.child);
            childWidget->SetParent(nullptr);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<ChildInput>([this](entityx::Entity entity, ChildInput &childInput){
                if (childInput.add) {
                    AddChild(childInput);
                } else {
                    RemoveChild(childInput);
                }
                entity.destroy();
            });
        }
    };
}

#endif //INANNA_CHILDINPUTSYSTEM_H
