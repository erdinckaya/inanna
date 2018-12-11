//
// Created by Erdınc Kaya on 2018-12-11.
//

#ifndef INANNA_LAYOUT_H
#define INANNA_LAYOUT_H

#include "../Types.h"

namespace Inanna {
    struct Layout {

        template<class T>
        explicit Layout(T v) {
            layouts.emplace_back(v);
        }

        template<class T, class... Args>
        explicit Layout(T t, Args... args) : Layout(args...) {
            layouts.emplace_back(t);
        }

        std::vector<std::pair<LayoutType, float>> layouts;
    };
}


#endif //INANNA_LAYOUT_H
