//
// Created by misterdortnal on 21.11.2018.
//

#include "entityx/deps/Dependencies.h"

#include "WindowManager.h"
#include "Systems/RenderSystem.h"
#include "Systems/ScaleSystem.h"
#include "Systems/SizeSystem.h"
#include "Systems/PositionSystem.h"
#include "Systems/RotationSystem.h"
#include "Components/Widget.h"

Inanna::WindowManager::WindowManager(float width, float height, Graphics *graphics)
        : width(width), height(height), graphics(graphics) {

    systems.add<RenderSystem>(graphics);
    systems.add<PositionSystem>();
    systems.add<SizeSystem>();
    systems.add<ScaleSystem>();
    systems.add<RotationSystem>();

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
        case SDLK_c: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
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
        default:
            break;
    }

#endif
}
