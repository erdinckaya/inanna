//
// Created by Erdınc Kaya on 2019-04-25.
//

#ifndef INANNA_CAMERASYSTEM_H
#define INANNA_CAMERASYSTEM_H


#include <entityx/System.h>
#include <tweeny.h>
#include "../Components/Camera.h"
#include "../../Graphics/Graphics.h"
#include "../Components/TweenAnim.h"

namespace Inanna {
    struct CameraSystem : public entityx::System<CameraSystem> {
        explicit CameraSystem(Graphics *graphics) : graphics(graphics) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

            entities.each<Camera>([this, dt](entityx::Entity entity, Camera &camera) {
                graphics->SetCameraViewPort(camera.port);
                cameraEnt = entity;
            });
        }

        static void SetCameraPos(const Vecf &pos) {
            if (cameraEnt.valid()) {
                auto camera = cameraEnt.component<Camera>();
                camera->port.x = pos.x;
                camera->port.y = pos.y;
            }
        }

        static void SetCameraPos(const float &x, const float &y) {
            if (cameraEnt.valid()) {
                auto camera = cameraEnt.component<Camera>();
                camera->port.x = x;
                camera->port.y = y;
            }
        }

        static Vecf GetCameraPos() {
            Vecf pos = Vecf(0, 0);
            if (cameraEnt.valid()) {
                auto camera = cameraEnt.component<Camera>();
                pos = Vecf(camera->port.x, camera->port.y);
            }
            return pos;
        }

    private:
        Graphics *graphics;
        static entityx::Entity cameraEnt;
    };


}

#endif //INANNA_CAMERASYSTEM_H
