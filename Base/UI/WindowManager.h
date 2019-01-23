//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_WINDOWMANAGER_H
#define INANNA_WINDOWMANAGER_H

#include <entityx/entityx.h>
#include "../Graphics/Graphics.h"
#include "UIFactory.h"

#include "Systems/RenderSystem.h"
#include "Systems/ScaleSystem.h"
#include "Systems/SizeSystem.h"
#include "Systems/PositionSystem.h"
#include "Systems/RotationSystem.h"
#include "Components/Widget.h"
#include "Events/ChildEvent.h"
#include "Systems/ChildSystem.h"
#include "Systems/DepthSystem.h"
#include "Systems/MouseInputSystem.h"
#include "Components/Interaction.h"
#include "Systems/MouseEventDispatcherSystem.h"
#include "MouseEventComponents/MouseDown.h"
#include "MouseEventComponents/MouseUp.h"
#include "Systems/ButtonSystem.h"
#include "../SpriteAnimation/SpriteAnimationFactory.h"


namespace Inanna {

    class WindowManager {
    public:
        explicit WindowManager(float width, float height, Graphics *graphics);

        void Update(entityx::TimeDelta dt);

        void Test(SDL_Keycode code);

        void TestMouseButton(SDL_MouseButtonEvent event);

        void TestMouseMotion(SDL_MouseMotionEvent event);

        void TestMouseWheel(SDL_MouseWheelEvent event);


        static UIFactory uiFactory;
        static SpriteAnimationFactory spriteAnimationFactory;
    private:
        float width;
        float height;

        Graphics *graphics;

#ifdef WINDOW_MANAGER_TEST
        entityx::Entity character;
#endif
    };
}


#endif //INANNA_WINDOWMANAGER_H
