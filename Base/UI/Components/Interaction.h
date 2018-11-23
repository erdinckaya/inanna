//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_INTERACTION_H
#define INANNA_INTERACTION_H

namespace Inanna {
    struct Interaction {
        explicit Interaction() : visible(true), mouse(true) {}
        explicit Interaction(const bool &visible, const bool &mouse) : visible(visible), mouse(mouse) {}

        bool visible;
        bool mouse;
    };
}
#endif //INANNA_INTERACTION_H
