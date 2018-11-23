//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_CHILDINPUTSYSTEM_H
#define INANNA_CHILDINPUTSYSTEM_H

#include <entityx/System.h>
#include "../Events/ChildEvent.h"
#include "../Components/Widget.h"
#include "../Components/Renderable.h"

namespace Inanna {

    class ChildSystem : public entityx::System<ChildSystem>, public ex::Receiver<ChildSystem> {
    public:
        explicit ChildSystem() = default;

        void configure(ex::EventManager &events) override {
            events.subscribe<ChildEvent>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

        }

        void receive(const ChildEvent &childEvent) {
            ChildEvent event = childEvent;

            auto child = event.child.component<Widget>();
            auto parent = event.parent.component<Widget>();

            if (childEvent.add) {
                child->SetParent(parent.entity());
                parent->AddChild(child.entity());
            } else {
                child->SetParent(ex::Entity());
                parent->RemoveChild(child.entity());
            }
        }
    };
}

#endif //INANNA_CHILDINPUTSYSTEM_H
