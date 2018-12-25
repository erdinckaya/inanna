//
// Created by Erdınc Kaya on 2018-12-21.
//

#ifndef INANNA_SCROLLVIEWERSYSTEM_H
#define INANNA_SCROLLVIEWERSYSTEM_H

#include <entityx/System.h>

#include "../Components/Widget.h"
#include "../Components/Root.h"
#include "../Components/Position.h"
#include "../Components/Sizable.h"
#include "../Widgets/ScrollViewer.h"

namespace Inanna {

    class ScrollVieverSystem : public entityx::System<ScrollVieverSystem> {
    public:
        explicit ScrollVieverSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<ScrollViever>([this](entityx::Entity entity, ScrollViever &scrollViever){

            });
        }
    };
}

#endif //INANNA_SCROLLVIEWERSYSTEM_H
