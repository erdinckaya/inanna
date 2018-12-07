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
        explicit Widget() = default;

        explicit Widget(const entityx::Entity &parent, const Veci &depth) : depth(depth), parent(parent), mouseWidget(false) {}

        void SetParent(const entityx::Entity parent) {
            this->parent = parent;
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

        bool HasParent() {
            return parent.valid();
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

        int ChildCount() {
            return static_cast<int>(children.size());
        }


        Veci depth;
        entityx::Entity parent;
        std::vector<entityx::Entity> children;
        bool mouseWidget;
    };
}

#endif //INANNA_WIDGET_H
