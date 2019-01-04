//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_RECTANGLE_H
#define INANNA_RECTANGLE_H

#include <ostream>
#include "Vec2.h"

namespace Inanna {
    template<class C>
    class Rect {
    public:
        Rect() : x(0), y(0), w(0), h(0) {}

        Rect(C x, C y, C w, C h) : x(x), y(y), w(w), h(h) {}

        Rect(Vec2<C> pos, Vec2<C> size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}

        ~Rect() = default;

        C x;
        C y;
        C w;
        C h;

        inline bool ValueInRange(C value, C min, C max) { return (value >= min) && (value <= max); }

        inline bool IsPointIn(Vec2<C> point) {
            return ValueInRange(point.x, x, x + w)
                   && ValueInRange(point.y, y, y + h);
        }

        inline bool IsIntersect(Rect<C> second) {
            return !(x > second.x + second.w || x + w < second.x || y > second.y + second.h || y + h < second.y);
        }

        inline Vec2<C> Length() const {
            return Vec2<C>(std::abs(w), std::abs(h));
        }

        std::string ToString() const {
            return "{" + std::to_string(x) + ", " + std::to_string(y)
                   + ", " + std::to_string(w) + "," + std::to_string(h) + "}";
        }

        friend inline bool operator==(const Rect &lhs, const Rect &rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h;
        }

        friend inline bool operator!=(const Rect &lhs, const Rect &rhs) {
            return !(lhs == rhs);
        }

        inline static std::pair<bool, Rect<C>> GetIntersect(Rect<C> first, Rect<C> second) {
            float x = std::max(first.x, second.x);
            float w = std::min(first.x + first.w, second.x + second.w);
            float y = std::max(first.y, second.y);
            float h = std::min(first.y + first.h, second.y + second.h);
            if (w >= x && h >= y) {
                return std::make_pair<bool, Rect<C>>(true, Rect<C>(x, y, w - x, h - y));
            }
            return std::make_pair<bool, Rect<C>>(false, Rect<C>());
        }

        friend std::ostream &operator<<(std::ostream &os, const Rect &rectangle) {
            os << "x: " << rectangle.x << " y: " << rectangle.y << " w: " << rectangle.w << " h: " << rectangle.h;
            return os;
        }

        REFLECT_TEMPLATE(Rect, C)
                            REFLECT_STRUCT_MEMBER_TEMPLATE(x)
                            REFLECT_STRUCT_MEMBER_TEMPLATE(y)
                            REFLECT_STRUCT_MEMBER_TEMPLATE(w)
                            REFLECT_STRUCT_MEMBER_TEMPLATE(h)
        REFLECT_STRUCT_END()
    };
    REFLECT_STRUCT_INIT_TEMPLATE(Rect)

    typedef Rect<float> Rectf;
    typedef Rect<double> Rectd;
    typedef Rect<int> Recti;
}


#endif //INANNA_RECTANGLE_H
