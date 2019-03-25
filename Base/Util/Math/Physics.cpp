//
// Created by Erdınc Kaya on 2019-03-14.
//

#include "Physics.h"

float Inanna::Physics::Jump(float v, float t, float g) {
    auto time = v / g;
    bool rising = true;
    if (t > time) {
        t -= time;
        rising = false;
    }
    if (rising) {
        return v * t  - g * t * t * 0.5f;
    }

    return v * v / g * 0.5f - g * t * t * 0.5f;
}

float Inanna::Physics::JumpWithDistanceAndTime(float distance, float risingTime, float elapsedTime) {
    float v  = 2 * distance / risingTime;
    float g = v / risingTime;
    return Jump(v, elapsedTime, g);
}
