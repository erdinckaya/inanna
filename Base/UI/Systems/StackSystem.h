//
// Created by Erdınc Kaya on 2018-12-11.
//

#ifndef INANNA_STACKSYSTEM_H
#define INANNA_STACKSYSTEM_H


#include <entityx/System.h>
#include "../Components/Widget.h"
#include "../Components/Root.h"
#include "../Widgets/Stack.h"
#include "../Components/Position.h"
#include "../Components/Sizable.h"

namespace Inanna {
    class StackSystem : public entityx::System<StackSystem> {
    public:
        explicit StackSystem() = default;

        void CalculateChildPosition(entityx::Entity entity, Stack &stack, Widget &widget, Sizable &sizable) {

            auto stackSize = Vecf(-1, -1);
            float offset = 0.0f;
            auto size = widget.ChildCount();
            for (int i = 0; i < size; ++i) {
                auto child = widget.GetChild(i);
                if (child.valid()) {
                    auto childSize = child.component<Sizable>();
                    auto childPos = child.component<Position>();
                    switch (stack.direction) {
                        case Horizontal: {
                            childPos->position = Vecf(offset, childPos->position.y);
                            offset += childSize->size.x;
                            break;
                        }
                        case Vertical: {
                            childPos->position = Vecf(childPos->position.x, offset);
                            offset += childSize->size.y;
                            break;
                        }
                    }

                    if (stack.direction == DirectionType::Horizontal) {
                        if (offset > stackSize.x) {
                            stackSize = Vecf(offset, stackSize.y);
                        }
                    } else {
                        if (childSize->size.x > stackSize.x) {
                            stackSize = Vecf(childSize->size.x, stackSize.y);
                        }
                    }

                    if (stack.direction == DirectionType::Vertical) {
                        if (offset > stackSize.y) {
                            stackSize = Vecf(stackSize.x, offset);
                        }
                    } else {
                        if (childSize->size.y > stackSize.y) {
                            stackSize = Vecf(stackSize.x, childSize->size.y);
                        }
                    }
                }
            }

            sizable.nativeSize = false;
            sizable.size = stackSize;

            if (entity.has_component<Interaction>()) {
                auto interaction = entity.component<Interaction>();
                interaction->visible = !(sizable.size == Vecf(0, 0));
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Stack, Widget, Sizable>(
                    [this](entityx::Entity entity, Stack &stack, Widget &widget, Sizable &sizable) {
                        CalculateChildPosition(entity, stack, widget, sizable);
                    });
        }
    };
}

#endif //INANNA_STACKSYSTEM_H
