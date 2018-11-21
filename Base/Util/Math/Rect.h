//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_RECTANGLE_H
#define INANNA_RECTANGLE_H

#include <ostream>
#include "Vec2.h"

namespace Inanna {
    template<class T>
    class Rect {
    public:
        Rect() : x(0), y(0), w(0), h(0) {}

        Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

        ~Rect() = default;

        T x;
        T y;
        T w;
        T h;

        inline bool IsPointIn(Vec2<T> point) {
            return ValueInRange(point.x, x, x + w)
                   && ValueInRange(point.y, y, y + h);
        }

        inline bool IsIntersect(Rect<T> second) {
            return !(x > second.x + second.w || x + w < second.x || y > second.y + second.h || y + h < second.y);
        }

        inline static std::pair<bool, Rect<T>> GetIntersect(Rect<T> first, Rect<T> second) {
            float x = std::max(first.x, second.x);
            float w = std::min(first.x + first.w, second.x + second.w);
            float y = std::max(first.y, second.y);
            float h = std::min(first.y + first.h, second.y + second.h);
            if (w >= x && h >= y) {
                return std::make_pair<bool, Rect<T>>(true, Rect<T>(x, y, w - x, h - y));
            }
            return std::make_pair<bool, Rect<T>>(false, Rect<T>());
        }

        friend std::ostream &operator<<(std::ostream &os, const Rect &rectangle) {
            os << "x: " << rectangle.x << " y: " << rectangle.y << " w: " << rectangle.w << " h: " << rectangle.h;
            return os;
        }
    };


    typedef Rect<float> Rectf;
    typedef Rect<double> Rectd;
    typedef Rect<int> Recti;
}


#endif //INANNA_RECTANGLE_H
