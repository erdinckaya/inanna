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

Inanna::WindowManager::WindowManager(float width, float height, Graphics *graphics)
        : width(width), height(height), graphics(graphics) {

    systems.add<RenderSystem>(graphics);
    systems.add<PositionSystem>();
    systems.add<SizeSystem>();
    systems.add<ScaleSystem>();
    systems.add<RotationSystem>();
    systems.add<ChildSystem>();
    systems.add<DepthSystem>();


    systems.add<MouseInputSystem>();

    systems.configure();
}

void Inanna::WindowManager::Update(entityx::TimeDelta dt) {
    systems.update_all(dt);
}

void Inanna::WindowManager::Test(SDL_Keycode code) {
#ifdef WINDOW_MANAGER_TEST
    switch (code) {
        case SDLK_k: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Scalable>(Vecf(1.5f, 1.5f));
            break;
        }
        case SDLK_a: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Position>(Vecf(100, 100));
            break;
        }
        case SDLK_b: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Sizable>(Vecf(100, 100));
            break;
        }
        case SDLK_r: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Rotation>(45);
            break;
        }
        case SDLK_w: {
            entityx::Entity entity = entities.create();
            entity.assign<Widget>();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Rotation>(45);
            entity.assign<Position>(Vecf(100, 100));
            entity.assign<Scalable>(Vecf(1, 1));
            break;
        }
        case SDLK_y: {
            entityx::Entity parent = entities.create();
            parent.assign<Root>();
            parent.assign<Widget>();
            parent.assign<Renderable>(Resources::PIECES.BLUE);
            parent.assign<Position>(Vecf(100, 100));
            parent.assign<Scalable>(Vecf(1, 1));


            entityx::Entity child = entities.create();
            child.assign<Widget>();
            child.assign<Renderable>(Resources::PIECES.RED);
            child.assign<Position>(Vecf(10, 10));
            child.assign<Scalable>(Vecf(1, 1));

            events.emit<ChildEvent>(parent, child, true);

            this->parent =parent;
            this->child =child;
            break;
        }
        case SDLK_c: {
            events.emit<ClearAllEvent>();
            break;
        }
        case SDLK_u: {
            events.emit<ChildEvent>(parent, child, false);
            break;
        }
        default:
            break;
    }

#endif
}

void Inanna::WindowManager::TestMouseButton(SDL_MouseButtonEvent event) {
    entityx::Entity input = entities.create();
    input.assign<MouseButton>(event);
}

void Inanna::WindowManager::TestMouseMotion(SDL_MouseMotionEvent event) {
    entityx::Entity input = entities.create();
    input.assign<MouseMotion>(event);
}

void Inanna::WindowManager::TestMouseWheel(SDL_MouseWheelEvent event) {
    entityx::Entity input = entities.create();
    input.assign<MouseWheel>(event);
}

