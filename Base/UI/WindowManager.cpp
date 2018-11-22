//
// Created by misterdortnal on 21.11.2018.
//

#include "WindowManager.h"
#include "Systems/RenderSystem.h"

Inanna::WindowManager::WindowManager(float width, float height, Graphics *graphics)
        : width(width), height(height), graphics(graphics) {
    systems.add<RenderSystem>(graphics);

    systems.configure();
}

void Inanna::WindowManager::Update(entityx::TimeDelta dt) {
    systems.update_all(dt);
}

void Inanna::WindowManager::Test() {
#ifdef WINDOW_MANAGER_TEST
    entityx::Entity entity = entities.create();
    entity.assign<Renderable>(Resources::PIECES.BLUE);
#endif
}
