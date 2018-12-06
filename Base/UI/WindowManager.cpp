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

Inanna::WindowManager::WindowManager(float width, float height, Graphics *graphics)
        : width(width), height(height), graphics(graphics) {
    
    systems.add<ChildSystem>();
    systems.add<DepthSystem>();

    systems.add<MouseInputSystem>();
    systems.add<MouseEventDispatcherSystem>();

    systems.add<SizeSystem>();
    systems.add<ScaleSystem>();
    systems.add<RotationSystem>();
    systems.add<PositionSystem>();
    systems.add<RenderSystem>(graphics);


    systems.configure();
}

void Inanna::WindowManager::Update(entityx::TimeDelta dt) {
    systems.update<ChildSystem>(dt);
    systems.update<DepthSystem>(dt);

    systems.update<MouseInputSystem>(dt);
    systems.update<MouseEventDispatcherSystem>(dt);

    systems.update<SizeSystem>(dt);
    systems.update<ScaleSystem>(dt);
    systems.update<RotationSystem>(dt);
    systems.update<PositionSystem>(dt);

    systems.update<RenderSystem>(dt);
}

void Inanna::WindowManager::Test(SDL_Keycode code) {
#ifdef WINDOW_MANAGER_TEST
    switch (code) {
        case SDLK_k: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Interaction>();
            entity.assign<Scalable>(Vecf(1.5f, 1.5f));
            break;
        }
        case SDLK_a: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Interaction>();
            entity.assign<Position>(Vecf(100, 100));
            break;
        }
        case SDLK_b: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Interaction>();
            entity.assign<Sizable>(Vecf(100, 100));
            break;
        }
        case SDLK_r: {
            entityx::Entity entity = entities.create();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Interaction>();
            entity.assign<Rotation>(45);
            break;
        }
        case SDLK_w: {
            entityx::Entity entity = entities.create();
            entity.assign<Widget>();
            entity.assign<Renderable>(Resources::PIECES.BLUE);
            entity.assign<Interaction>();
            entity.assign<Rotation>(45);
            entity.assign<Position>(Vecf(100, 100));
            entity.assign<Scalable>(Vecf(1, 1));
            break;
        }
        case SDLK_y: {
            entityx::Entity parent = entities.create();
            entityx::Entity child = entities.create();


            parent.assign<Root>();
            parent.assign<Widget>();
            parent.assign<Renderable>(Resources::PIECES.BLUE);
            parent.assign<Interaction>();
            parent.assign<Position>(Vecf(100, 100));
            parent.assign<Scalable>(Vecf(1, 1));



            child.assign<Widget>();
            child.assign<Renderable>(Resources::PIECES.RED);
            child.assign<Interaction>();
            child.assign<Position>(Vecf(10, 10));
            child.assign<Scalable>();
            child.assign<MouseDragStart>([](entityx::Entity entity, SDL_MouseMotionEvent event) {
                printf("MouseDragStart %s\n", entity.component<Renderable>()->target.id);
            });
            child.assign<MouseDrag>([](entityx::Entity entity, SDL_MouseMotionEvent event) {
                Vecf pos = entity.component<Position>()->position;
                entity.component<Position>()->position = Vecf(pos.x + event.xrel, pos.y + event.yrel);
            });
            child.assign<MouseDragEnd>([](entityx::Entity entity, SDL_MouseMotionEvent event) {
                printf("MouseDragEnd %s\n", entity.component<Renderable>()->target.id);
            });

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
    printf("Entity count %d\n", static_cast<int>(entities.size()));

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

