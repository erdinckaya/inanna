//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_SIZE_H
#define INANNA_SIZE_H
#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct Sizable {
        explicit Sizable(const Vecf &size = Vecf(0, 0)) : size(size) {}
        Vecf size;
    };
}
#endif //INANNA_SIZE_H
