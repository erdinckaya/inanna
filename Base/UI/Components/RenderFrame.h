//
// Created by Erdınc Kaya on 2018-12-12.
//

#ifndef INANNA_RENDERFRAME_H
#define INANNA_RENDERFRAME_H

#include "../../Util/Math/Rect.h"

namespace Inanna {
    struct RenderFrame {
        explicit RenderFrame() = default;
        explicit RenderFrame(const Rectf &frame) : frame(frame) {}

        Rectf frame;
    };
}

#endif //INANNA_RENDERFRAME_H
