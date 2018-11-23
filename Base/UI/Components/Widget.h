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

        explicit Widget(const entityx::Entity &parent, const Vecf &depth): depth(depth), parent(parent), hasParent(false) {}

        Vecf depth;
        entityx::Entity parent;
        std::vector<entityx::Entity> children;
        bool hasParent;

        void SetParent(const entityx::Entity parent) {
            this->parent = parent;
            hasParent = true;
        }

        void RemoveParent() {
            hasParent = false;
        }

        void RemoveChild(const entityx::Entity child) {
            int size = (int) children.size();
            for (int i = size - 1; i > -1; --i) {
                if (children[i] == child) {
                    children.erase(children.begin() + i);
                    break;
                }
            }
        }

        void AddChild(const entityx::Entity child) {
            children.emplace_back(child);
        }

        entityx::Entity GetChild(int index) {
            if (index > -1 && index < children.size()) {
                return children[index];
            }
            return entityx::Entity();
        }
    };
}

#endif //INANNA_WIDGET_H
