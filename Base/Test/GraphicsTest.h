//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_GRAPHICSTEST_H
#define INANNA_GRAPHICSTEST_H

#include "../Graphics/Graphics.h"

class GraphicsTest {

public:



    void Test() {
        SDL_Event event{};
        while (true) {

            const Uint32 start_time_ms = SDL_GetTicks();

            const Uint32 ms_per_frame = 1000/*ms*/ / 60;
            const Uint32 elapsed_time_ms = SDL_GetTicks() - start_time_ms;
            if (elapsed_time_ms < ms_per_frame) {
                SDL_Delay(ms_per_frame - elapsed_time_ms);
            }
        }
    }

    void TestInit() {
        Inanna::Graphics graphics(900, 900, SDL_WINDOW_OPENGL);

    }

};

#endif //INANNA_GRAPHICSTEST_H
