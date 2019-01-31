//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_GAME_H
#define INANNA_GAME_H


#include <entityx/quick.h>
#include "../Graphics/Graphics.h"
#include "Util/KeyPatterns.h"


namespace Inanna {
    class Game : public entityx::EntityX {
    public:
        explicit Game(Graphics* graphics);

        void Update(entityx::TimeDelta dt);

        void Test(SDL_Keycode code);


        KeyPatterns Patterns;
        entityx::Entity Player;
        entityx::Entity Rival;

        static Game* Instance;

    private:
        Graphics* graphics;
    };
}




#endif //INANNA_GAME_H
