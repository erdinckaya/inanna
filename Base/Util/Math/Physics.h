//
// Created by Erdınc Kaya on 2019-03-14.
//

#ifndef INANNA_PHYSICS_H
#define INANNA_PHYSICS_H


namespace Inanna {
    class Physics {

    public:
        explicit Physics() = default;

        static float Jump(float v, float t, float g = GRAVITY);
        static float JumpWithDistanceAndTime(float distance, float risingTime, float elapsedTime);

        static float PushBack(float v, float t, float g = GRAVITY);
        static float PushBackWithDistanceAndTime(float distance, float time, float elapsedTime);

        static constexpr float GRAVITY = 9.81f;

    };
}


#endif //INANNA_PHYSICS_H
