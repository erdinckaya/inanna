//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_WIDGET_H
#define INANNA_WIDGET_H

#include <entityx/System.h>
#include "../../Util/Math/Vec2.h"
#include <vector>

namespace Inanna {

    struct Widget {
        explicit Widget() {}

        explicit Widget(const entityx::Entity* parent, const Vecf depth): depth(depth), parent(parent) {}

        Vecf depth;
        const entityx::Entity* parent;
        std::vector<const entityx::Entity*> children;

        void SetParent(const entityx::Entity* parent) {
            this->parent = parent;
        }

        void RemoveChild(const entityx::Entity* child) {
            int size = (int) children.size();
            for (int i = size - 1; i > -1; --i) {
                if (children[i] == child) {
                    children.erase(children.begin() + i);
                    break;
                }
            }
        }

        void AddChild(const entityx::Entity* child) {
            children.emplace_back(child);
        }
    };
}

#endif //INANNA_WIDGET_H
