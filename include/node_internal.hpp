#pragma once

struct vec2 {
    float x, y;

    vec2() : x(0), y(0) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}

    float length() const { return sqrt(x * x + y * y); }
    float dot(const vec2& vec) const { return x * vec.x + y * vec.y; }

    vec2 normalized() const {
        float len = length();

        if (len != 0) {
            return vec2(x / len, y / len);
        }

        return *this;
    }

    vec2 operator+(const vec2& vec) const { return vec2(x + vec.x, y + vec.y); }
    void operator+=(const vec2& vec) {
        x += vec.x;
        y += vec.y;
        return;
    }
    vec2 operator-(const vec2& vec) const { return vec2(x - vec.x, y - vec.y); }
    void operator-=(const vec2& vec) {
        x -= vec.x;
        y -= vec.y;
        return;
    }
    vec2 operator*(const float scalar) const { return vec2(x * scalar, y * scalar); }
    vec2 operator*(const vec2& vec)    const { return vec2(x * vec.x, y * vec.y); }
    vec2 operator/(const float scalar) const { return vec2(x / scalar, y / scalar); }
    vec2 operator/(const vec2& vec)    const { return vec2(x / vec.x, y / vec.y); }
};