//
// Created by Erdınc Kaya on 2018-12-11.
//

#ifndef INANNA_LAYOUTSYSTEM_H
#define INANNA_LAYOUTSYSTEM_H

#include <entityx/System.h>
#include "../Components/Layout.h"
#include "../Components/Widget.h"
#include "../Components/Position.h"
#include "../Components/Sizable.h"

namespace Inanna {
    class LayoutSystem : public entityx::System<LayoutSystem> {
    public:
        explicit LayoutSystem() = default;

        void
        CalculateLayout(entityx::Entity entity, Layout &layoutComp, Widget &widget, Sizable &sizable, Position &position) {
            if (widget.HasParent()) {
                auto parent = widget.parent;
                auto p_size = parent.component<Sizable>();
                auto p_pos = parent.component<Position>();

                auto layoutCount = (int)layoutComp.layouts.size();
                for (int i = layoutCount - 1; i > -1; --i) {
                    auto type = layoutComp.layouts[i].first;
                    auto offset = layoutComp.layouts[i].second;

                    switch (type) {
                        case LT_LEFT: {
                            position.position = Vecf(offset, position.position.y);
                            break;
                        }
                        case LT_RIGHT: {
                            position.position = Vecf(p_size->size.x - offset, position.position.y);
                            break;
                        }
                        case LT_CENTER: {
                            auto c_x = (p_size->size.x - sizable.size.x) * 0.5f;
                            auto c_y = (p_size->size.y - sizable.size.y) * 0.5f;
                            position.position = Vecf(c_x, c_y);
                            break;
                        }
                        case LT_HORIZONTAL_lCENTER: {
                            auto c_x = (p_size->size.x - sizable.size.x) * 0.5f;
                            position.position = Vecf(c_x, position.position.y);
                            break;
                        }
                        case LT_VERTICAL_CENTER: {
                            auto c_y = (p_size->size.y - sizable.size.y) * 0.5f;
                            position.position = Vecf(position.position.x, c_y);
                            break;
                        }
                        case LT_TOP: {
                            position.position = Vecf(position.position.x, offset);
                            break;
                        }
                        case LT_BOTTOM: {
                            position.position = Vecf(position.position.x, p_size->size.y - offset);
                            break;
                        }
                    }
                }
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Layout, Widget, Sizable, Position>(
                    [this](entityx::Entity entity, Layout &layout, Widget &widget, Sizable &sizable,
                           Position &position) {
                        CalculateLayout(entity, layout, widget, sizable, position);
                    });
        }
    };
}

#endif //INANNA_LAYOUTSYSTEM_H
