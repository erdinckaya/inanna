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
#include "Command/Systems/DamageReceiveCommandSystem.h"
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


Inanna::Game* Inanna::Game::Instance = nullptr;

Inanna::Game::Game(Graphics* graphics) : graphics(graphics) {
    systems.add<KeyInputSystem>();
    systems.add<HitCommandSystem>();
    systems.add<MoveCommandSystem>();
    systems.add<CrouchCommandSystem>();
    systems.add<JumpCommandSystem>();
    systems.add<JumpBackCommandSystem>();
    systems.add<RunCommandSystem>();
    systems.add<RollCommandSystem>();
    systems.add<OryuCommandSystem>();
    systems.add<DamageReceiveCommandSystem>();


    systems.add<HitSystem>();
    systems.add<CrouchSystem>();
    systems.add<MoveCharacterSystem>();
    systems.add<JumpCharacterSystem>();
    systems.add<JumpBackSystem>();
    systems.add<RunSystem>();
    systems.add<RollSystem>();
    systems.add<OryuSystem>();


    systems.add<SpriteAnimationSystem>();
    systems.add<SpritePositionSystem>();
    systems.add<SpriteFacingSystem>();
    systems.add<SpriteRenderSystem>(graphics);
    systems.add<SpriteGizmoSystem>(graphics);
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
    systems.update<RollCommandSystem>(dt);
    systems.update<OryuCommandSystem>(dt);
    systems.update<DamageReceiveCommandSystem>(dt);


    systems.update<HitSystem>(dt);
    systems.update<CrouchSystem>(dt);
    systems.update<MoveCharacterSystem>(dt);
    systems.update<JumpCharacterSystem>(dt);
    systems.update<JumpBackSystem>(dt);
    systems.update<RunSystem>(dt);
    systems.update<RollSystem>(dt);
    systems.update<OryuSystem>(dt);


    systems.update<SpriteAnimationSystem>(dt);
    systems.update<SpritePositionSystem>(dt);
    systems.update<SpriteFacingSystem>(dt);
    systems.update<SpriteRenderSystem>(dt);
    systems.update<SpriteGizmoSystem>(dt);
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

            break;
        }
        case SDLK_2: {
            Rival = entities.create();
            auto comp = Rival.assign<SpriteAnimation>(AnimationData::KYO_IDLE);
            Rival.assign<Time>(0);
            comp->loop = true;
            Rival.assign<Position>(Vecf(100, 100));
            Rival.assign<Facing>(false);
            Rival.assign<Character>("Kyo");
            Rival.assign<UserKeyHistory>();
            Rival.assign<CharacterState>();
            Rival.assign<SpriteZ>(1);
            Rival.assign<Health>(100);

            break;
        }
        default:
            break;
    }

#endif
}

