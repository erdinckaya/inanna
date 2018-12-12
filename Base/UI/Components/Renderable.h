
//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_RENDERABLE_H
#define INANNA_RENDERABLE_H

#include "../../Util/Math/Vec2.h"
#include "../../Util/Math/Rect.h"
#include "../../../Assets/Resources.h"

namespace Inanna {
    struct Renderable {
        explicit Renderable(const ImageAsset &target = ImageAsset(), const Vecf &pos = Vecf(0, 0),
                            const Vecf &size = Vecf(0, 0),
                            const Vecf &scale = Vecf(1, 1), const float &rotation = 0, Rectf frame = Rectf(0, 0, 0, 0))
                : target(target), pos(pos),
                  size(size),
                  scale(scale),
                  rotation(rotation),
                  frame(frame),
                  hasFrame(false) {
            if (this->size == Vecf(0, 0)) {
                this->size = Vecf(target.w, target.h);
            }
        }

        ImageAsset target;
        Vecf pos;
        Vecf size;
        Vecf scale;
        float rotation;
        Rectf frame;
        Rectf renderContext;
        bool hasFrame;
    };
}

#endif //INANNA_RENDERABLE_H
