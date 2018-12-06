
#ifndef INANNA_VEC2_H
#define INANNA_VEC2_H

#include <cmath>

namespace Inanna {

    template<class T>
    class Vec2 {
    public:
        T x, y;

        Vec2() : x(0), y(0) {}

        Vec2(T x, T y) : x(x), y(y) {}

        Vec2(const Vec2 &v) : x(v.x), y(v.y) {}

        inline Vec2 &operator=(const Vec2 &v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        inline Vec2 operator+(Vec2 &v) {
            return Vec2(x + v.x, y + v.y);
        }

        inline Vec2 operator-(Vec2 &v) {
            return Vec2(x - v.x, y - v.y);
        }

        inline Vec2 &operator+=(Vec2 &v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        inline Vec2 &operator-=(Vec2 &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        inline Vec2 operator+(double s) {
            return Vec2(x + s, y + s);
        }

        inline Vec2 operator-(double s) {
            return Vec2(x - s, y - s);
        }

        inline Vec2 operator*(double s) {
            return Vec2(x * s, y * s);
        }

        inline Vec2 operator/(double s) {
            return Vec2(x / s, y / s);
        }


        inline Vec2 &operator+=(double s) {
            x += s;
            y += s;
            return *this;
        }

        inline Vec2 &operator-=(double s) {
            x -= s;
            y -= s;
            return *this;
        }

        inline Vec2 &operator*=(double s) {
            x *= s;
            y *= s;
            return *this;
        }

        inline Vec2 &operator/=(double s) {
            x /= s;
            y /= s;
            return *this;
        }


        friend inline bool operator==(const Vec2& lhs, const Vec2& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend inline bool operator!=(const Vec2& lhs, const Vec2& rhs) {
            return !(lhs == rhs);
        }

        inline void Set(T x, T y) {
            this->x = x;
            this->y = y;
        }

        inline void Rotate(double deg) {
            double theta = deg / 180.0 * M_PI;
            double c = cos(theta);
            double s = sin(theta);
            double tx = x * c - y * s;
            double ty = x * s + y * c;
            x = tx;
            y = ty;
        }

        inline Vec2 &Normalize() {
            if (Length() == 0) return *this;
            *this *= (1.0 / Length());
            return *this;
        }

        inline float Distance(Vec2 v) const {
            Vec2 d(v.x - x, v.y - y);
            return d.Length();
        }

        inline float Length() const {
            return std::sqrt(x * x + y * y);
        }

        inline void Truncate(double length) {
            double angle = atan2f(y, x);
            x = length * cos(angle);
            y = length * sin(angle);
        }

        inline Vec2 Ortho() const {
            return Vec2(y, -x);
        }

        inline static float Dot(Vec2 v1, Vec2 v2) {
            return v1.x * v2.x + v1.y * v2.y;
        }

        inline static float Cross(Vec2 v1, Vec2 v2) {
            return (v1.x * v2.y) - (v1.y * v2.x);
        }
    };

    typedef Vec2<float> Vecf;
    typedef Vec2<double> Vecd;
    typedef Vec2<int> Veci;
}

#endif