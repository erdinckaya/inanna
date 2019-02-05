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
#include "Components/MoveState.h"
#include "Command/Systems/CrouchCommandSystem.h"
#include "Systems/CrouchSystem.h"
#include "Command/Systems/JumpCommandSystem.h"
#include "Systems/JumpCharacterSystem.h"
#include "Components/JumpState.h"
#include "Command/Systems/JumpBackCommandSystem.h"
#include "Systems/JumpBackSystem.h"
#include "Command/Systems/RunCommandSystem.h"
#include "Systems/RunSystem.h"


Inanna::Game* Inanna::Game::Instance = nullptr;

Inanna::Game::Game(Graphics* graphics) : graphics(graphics) {
    systems.add<KeyInputSystem>();
    systems.add<HitCommandSystem>();
    systems.add<MoveCommandSystem>();
    systems.add<CrouchCommandSystem>();
    systems.add<JumpCommandSystem>();
    systems.add<JumpBackCommandSystem>();
    systems.add<RunCommandSystem>();


    systems.add<HitSystem>();
    systems.add<CrouchSystem>();
    systems.add<MoveCharacterSystem>();
    systems.add<JumpCharacterSystem>();
    systems.add<JumpBackSystem>();
    systems.add<RunSystem>();


    systems.add<SpriteAnimationSystem>();
    systems.add<SpritePositionSystem>();
    systems.add<SpriteRenderSystem>(graphics);
    systems.configure();

    Patterns.Init("../Resources/Data/key_patterns.json");
}

void Inanna::Game::Update(entityx::TimeDelta dt) {
    systems.update<KeyInputSystem>(dt);
    systems.update<HitCommandSystem>(dt);
    systems.update<MoveCommandSystem>(dt);
    systems.update<CrouchCommandSystem>(dt);
    systems.update<JumpCommandSystem>(dt);
    systems.update<JumpBackCommandSystem>(dt);
    systems.update<RunCommandSystem>(dt);


    systems.update<HitSystem>(dt);
    systems.update<CrouchSystem>(dt);
    systems.update<MoveCharacterSystem>(dt);
    systems.update<JumpCharacterSystem>(dt);
    systems.update<JumpBackSystem>(dt);
    systems.update<RunSystem>(dt);


    systems.update<SpriteAnimationSystem>(dt);
    systems.update<SpritePositionSystem>(dt);
    systems.update<SpriteRenderSystem>(dt);
}


void Inanna::Game::Test(SDL_Keycode code) {
#ifdef WINDOW_MANAGER_TEST
    switch (code) {
        case SDLK_n: {
            Player = entities.create();
            auto comp = Player.assign<SpriteAnimation>(AnimationData::KYO_IDLE);
            Player.assign<Time>(0);
            comp->loop = true;
            Player.assign<Position>(Vecf(100, 100));
            Player.assign<Character>("Kyo");
            Player.assign<UserKeyHistory>();
            Player.assign<MoveState>();
            Player.assign<JumpState>();

            break;
        }
        default:
            break;
    }

#endif
}

