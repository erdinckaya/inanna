//
// Created by Erdınc Kaya on 2019-01-28.
//

#include "Game.h"


#include "../../Assets/AnimationData.h"
#include "../SpriteAnimation/Systems/SpriteAnimationSystem.h"
#include "../SpriteAnimation/Systems/SpritePositionSystem.h"
#include "../SpriteAnimation/Systems/SpriteRenderSystem.h"
#include "Systems/MoveCharacterSystem.h"
#include "Systems/KeyInputSystem.h"
#include "Command/Systems/MoveCommandSystem.h"
#include "Command/Systems/HitCommandSystem.h"
#include "Systems/HitSystem.h"
#include "Command/Systems/CrouchCommandSystem.h"
#include "Command/Systems/DamageCommandSystem.h"
#include "Systems/CrouchSystem.h"
#include "Command/Systems/JumpCommandSystem.h"
#include "Systems/JumpCharacterSystem.h"
#include "Command/Systems/JumpBackCommandSystem.h"
#include "Systems/JumpBackSystem.h"
#include "Command/Systems/RunCommandSystem.h"
#include "Systems/RunSystem.h"
#include "Components/CharacterState.h"
#include "Command/Systems/RollCommandSystem.h"
#include "Systems/RollSystem.h"
#include "Command/Systems/OryuCommandSystem.h"
#include "Systems/OryuSystem.h"
#include "../SpriteAnimation/Systems/SpriteGizmoSystem.h"
#include "Components/Facing.h"
#include "../SpriteAnimation/Systems/SpriteFacingSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/CollisionSystem.h"
#include "Components/Gizmo.h"
#include "Components/Camera.h"
#include "Systems/CameraSystem.h"
#include "Systems/TweenAnimSystem.h"


Inanna::Game *Inanna::Game::Instance = nullptr;

Inanna::Game::Game(Graphics *graphics) : graphics(graphics) {
    systems.add<KeyInputSystem>();
    systems.add<HitCommandSystem>();
    systems.add<MoveCommandSystem>();
    systems.add<CrouchCommandSystem>();
    systems.add<JumpCommandSystem>();
    systems.add<JumpBackCommandSystem>();
    systems.add<RunCommandSystem>();
    systems.add<RollCommandSystem>();
    systems.add<OryuCommandSystem>();
    systems.add<DamageCommandSystem>();


    systems.add<HitSystem>();
    systems.add<CrouchSystem>();
    systems.add<MoveCharacterSystem>();
    systems.add<JumpCharacterSystem>();
    systems.add<JumpBackSystem>();
    systems.add<RunSystem>();
    systems.add<RollSystem>();
    systems.add<OryuSystem>();
    systems.add<CollisionSystem>();
    systems.add<DamageSystem>();


    systems.add<SpriteAnimationSystem>();
    systems.add<SpritePositionSystem>();
    systems.add<SpriteFacingSystem>();
    systems.add<SpriteRenderSystem>(graphics);
    systems.add<SpriteGizmoSystem>(graphics);


    systems.add<TweenAnimSystem>();
    systems.add<CameraSystem>(graphics);
    systems.configure();

    Patterns.Init("../Resources/Data/key_patterns.json");

    entities.create().assign<Camera>(Rectf(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Inanna::Game::Update(entityx::TimeDelta dt) {
    systems.update<KeyInputSystem>(dt);
    systems.update<HitCommandSystem>(dt);
    systems.update<MoveCommandSystem>(dt);
    systems.update<CrouchCommandSystem>(dt);
    systems.update<JumpCommandSystem>(dt);
    systems.update<JumpBackCommandSystem>(dt);
    systems.update<RunCommandSystem>(dt);
    systems.update<RollCommandSystem>(dt);
    systems.update<OryuCommandSystem>(dt);
    systems.update<DamageCommandSystem>(dt);


    systems.update<HitSystem>(dt);
    systems.update<CrouchSystem>(dt);
    systems.update<MoveCharacterSystem>(dt);
    systems.update<JumpCharacterSystem>(dt);
    systems.update<JumpBackSystem>(dt);
    systems.update<RunSystem>(dt);
    systems.update<RollSystem>(dt);
    systems.update<OryuSystem>(dt);

    systems.update<CollisionSystem>(dt);
    systems.update<DamageSystem>(dt);


    systems.update<SpriteAnimationSystem>(dt);
    systems.update<SpritePositionSystem>(dt);
    systems.update<SpriteFacingSystem>(dt);
    systems.update<SpriteRenderSystem>(dt);
    systems.update<SpriteGizmoSystem>(dt);

    systems.update<TweenAnimSystem>(dt);
    systems.update<CameraSystem>(dt);
}


void Inanna::Game::Test(SDL_Keycode code) {
#ifdef WINDOW_MANAGER_TEST
    switch (code) {
        case SDLK_1: {
            Player = entities.create();
            auto comp = Player.assign<SpriteAnimation>(AnimationData::KYO_IDLE);
            Player.assign<Time>(0);
            comp->loop = true;
            Player.assign<Position>(Vecf(100, 100));
            Player.assign<Facing>();
            Player.assign<Character>("Kyo");
            Player.assign<UserKeyHistory>();
            Player.assign<CharacterState>();
            Player.assign<SpriteZ>(0);
            Player.assign<Health>(100);
            Player.assign<Collidable>();
            Player.assign<Gizmo>(true);

            break;
        }
        case SDLK_2: {
            Rival = entities.create();
            auto comp = Rival.assign<SpriteAnimation>(AnimationData::KYO_IDLE);
            Rival.assign<Time>(0);
            comp->loop = true;
            Rival.assign<Position>(Vecf(500, 100));
            Rival.assign<Facing>(false);
            Rival.assign<Character>("Kyo");
            Rival.assign<UserKeyHistory>();
            Rival.assign<CharacterState>();
            Rival.assign<SpriteZ>(1);
            Rival.assign<Health>(100);
            Rival.assign<Collidable>();
            Rival.assign<Gizmo>(true);

            break;
        }
        case SDLK_o: {
            auto pos = CameraSystem::GetCameraPos();

            auto ent = entities.create();
            auto tween = tweeny::from(pos.x).to(pos.x + 100.0f).during(1000)
                    .via(tweeny::easing::backInOutEasing())
                    .onStep([&pos](tweeny::tween<float> &t, float x) {
                        CameraSystem::SetCameraPos(x, pos.y);
                        return false;
                    });
            ent.assign<TweenAnim>(tween)->OnStart([](){printf("Start\n");}).OnComplete([](){printf("Complete\n");});

            break;
        }
        case SDLK_p: {
            auto pos = CameraSystem::GetCameraPos();

            auto ent = entities.create();
            auto tween = tweeny::from(pos.x).to(pos.x - 100.0f).during(1000)
                    .via(tweeny::easing::backInOutEasing())
                    .onStep([&pos](tweeny::tween<float> &t, float x) {
                        CameraSystem::SetCameraPos(x, pos.y);
                        return false;
                    });
            ent.assign<TweenAnim>(tween, [](){printf("Start\n");}, [](){printf("Complete\n");});
            break;
        }

        default:
            break;
    }

#endif
}

