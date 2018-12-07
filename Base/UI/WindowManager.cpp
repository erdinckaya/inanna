//
// Created by misterdortnal on 21.11.2018.
//

#include "WindowManager.h"
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

Inanna::UIFactory Inanna::WindowManager::uiFactory;

Inanna::WindowManager::WindowManager(float width, float height, Graphics *graphics)
        : width(width), height(height), graphics(graphics) {

    uiFactory.systems.add<ChildSystem>();
    uiFactory.systems.add<DepthSystem>();

    uiFactory.systems.add<MouseInputSystem>();
    uiFactory.systems.add<MouseEventDispatcherSystem>();

    uiFactory.systems.add<SizeSystem>();
    uiFactory.systems.add<ScaleSystem>();
    uiFactory.systems.add<RotationSystem>();
    uiFactory.systems.add<PositionSystem>();
    uiFactory.systems.add<RenderSystem>(graphics);


    uiFactory.systems.configure();
}

void Inanna::WindowManager::Update(entityx::TimeDelta dt) {
    uiFactory.systems.update<ChildSystem>(dt);
    uiFactory.systems.update<DepthSystem>(dt);

    uiFactory.systems.update<MouseInputSystem>(dt);
    uiFactory.systems.update<MouseEventDispatcherSystem>(dt);

    uiFactory.systems.update<SizeSystem>(dt);
    uiFactory.systems.update<ScaleSystem>(dt);
    uiFactory.systems.update<RotationSystem>(dt);
    uiFactory.systems.update<PositionSystem>(dt);

    uiFactory.systems.update<RenderSystem>(dt);
}

void Inanna::WindowManager::Test(SDL_Keycode code) {
#ifdef WINDOW_MANAGER_TEST
    switch (code) {
        case SDLK_y: {
            entityx::Entity parent = uiFactory.CreateCanvas(Vecf(100, 100));
            entityx::Entity child = uiFactory.CreateCanvas(Vecf(10, 10));

            parent.assign<Root>();
            parent.component<Renderable>()->target = Resources::PIECES.BLUE;
            parent.assign<MouseClick>([](entityx::Entity entity, SDL_MouseButtonEvent event) {
                printf("MouseClick %s\n", entity.component<Renderable>()->target.id);
            });


            child.component<Renderable>()->target = Resources::PIECES.RED;
            child.assign<MouseClick>([](entityx::Entity entity, SDL_MouseButtonEvent event) {
                printf("MouseClick %s\n", entity.component<Renderable>()->target.id);
            });

            uiFactory.events.emit<ChildEvent>(parent, child, true);
            break;
        }
        case SDLK_p: {
            break;
        }
        case SDLK_c: {
            uiFactory.events.emit<ClearAllEvent>();
            break;
        }
        default:
            break;
    }
    printf("Entity count %d\n", static_cast<int>(uiFactory.entities.size()));

#endif
}

void Inanna::WindowManager::TestMouseButton(SDL_MouseButtonEvent event) {
    entityx::Entity input = uiFactory.entities.create();
    input.assign<MouseButton>(event);
}

void Inanna::WindowManager::TestMouseMotion(SDL_MouseMotionEvent event) {
    entityx::Entity input = uiFactory.entities.create();
    input.assign<MouseMotion>(event);
}

void Inanna::WindowManager::TestMouseWheel(SDL_MouseWheelEvent event) {
    entityx::Entity input = uiFactory.entities.create();
    input.assign<MouseWheel>(event);
}

