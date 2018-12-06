//
// Created by Erdınc Kaya on 2018-12-06.
//

#ifndef INANNA_MOUSEEVENTDISPATCHERSYSTEM_H
#define INANNA_MOUSEEVENTDISPATCHERSYSTEM_H

#include <entityx/Entity.h>
#include <entityx/System.h>
#include "../MouseEvents/MouseDownEvent.h"
#include "../MouseEvents/MouseUpEvent.h"
#include "../MouseEvents/MouseDragStartEvent.h"
#include "../MouseEvents/MouseDragEvent.h"
#include "../MouseEvents/MouseDragEndEvent.h"
#include "../MouseEventComponents/MouseDown.h"
#include "../MouseEventComponents/MouseUp.h"
#include "../MouseEventComponents/MouseClick.h"
#include "../MouseEventComponents/MouseDragStart.h"
#include "../MouseEventComponents/MouseDrag.h"
#include "../MouseEventComponents/MouseDragEnd.h"

namespace Inanna {
    class MouseEventDispatcherSystem
            : public entityx::System<MouseEventDispatcherSystem>, public entityx::Receiver<MouseEventDispatcherSystem> {
    public:
        explicit MouseEventDispatcherSystem() = default;

        void configure(ex::EventManager &events) override {
            events.subscribe<MouseDownEvent>(*this);
            events.subscribe<MouseUpEvent>(*this);
            events.subscribe<MouseClickEvent>(*this);
            events.subscribe<MouseDragStartEvent>(*this);
            events.subscribe<MouseDragEvent>(*this);
            events.subscribe<MouseDragEndEvent>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

        }

        void receive(const MouseDownEvent &event) {
            if (!event.entity.valid()) {
                return;
            }

            auto entity = event.entity;
            if (entity.has_component<MouseDown>()) {
                entity.component<MouseDown>()->callback(event.entity, event.mouseEvent);
            }
        }

        void receive(const MouseUpEvent &event) {
            if (!event.entity.valid()) {
                return;
            }

            auto entity = event.entity;
            if (entity.has_component<MouseUp>()) {
                entity.component<MouseUp>()->callback(event.entity, event.mouseEvent);
            }
        }

        void receive(const MouseClickEvent &event) {
            if (!event.entity.valid()) {
                return;
            }

            auto entity = event.entity;
            if (entity.has_component<MouseClick>()) {
                entity.component<MouseClick>()->callback(event.entity, event.mouseEvent);
            }
        }

        void receive(const MouseDragStartEvent &event) {
            if (!event.entity.valid()) {
                return;
            }

            auto entity = event.entity;
            if (entity.has_component<MouseDragStart>()) {
                entity.component<MouseDragStart>()->callback(event.entity, event.mouseEvent);
            }
        }

        void receive(const MouseDragEvent &event) {
            if (!event.entity.valid()) {
                return;
            }

            auto entity = event.entity;
            if (entity.has_component<MouseDrag>()) {
                entity.component<MouseDrag>()->callback(event.entity, event.mouseEvent);
            }
        }

        void receive(const MouseDragEndEvent &event) {
            if (!event.entity.valid()) {
                return;
            }

            auto entity = event.entity;
            if (entity.has_component<MouseDragEnd>()) {
                entity.component<MouseDragEnd>()->callback(event.entity, event.mouseEvent);
            }
        }
    };
}
#endif //INANNA_MOUSEEVENTDISPATCHERSYSTEM_H
