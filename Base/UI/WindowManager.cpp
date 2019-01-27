//
// Created by misterdortnal on 21.11.2018.
//

#include "WindowManager.h"
#include "../World.h"
#include "Systems/LayoutSystem.h"
#include "Systems/StackSystem.h"
#include "Systems/ScrollViewerSystem.h"
#include "Systems/RenderFrameSystem.h"
#include "../../Assets/AnimationData.h"
#include "../SpriteAnimation/Systems/SpriteAnimationSystem.h"
#include "../SpriteAnimation/Systems/SpritePositionSystem.h"
#include "../SpriteAnimation/Systems/SpriteRenderSystem.h"
#include "../Game/Systems/MoveCharacterSystem.h"
#include "../Game/Systems/KeyInputSystem.h"
#include "../Game/Command/Systems/InputCommandSystem.h"
#include "../Game/Command/Systems/MoveCommandSystem.h"
#include "../Game/Components/MoveState.h"
#include "../Game/Util/MoveStates.h"


Inanna::UIFactory Inanna::WindowManager::uiFactory;
Inanna::SpriteAnimationFactory Inanna::WindowManager::spriteAnimationFactory;

Inanna::WindowManager::WindowManager(float width, float height, Graphics *graphics)
        : width(width), height(height), graphics(graphics) {

    uiFactory.systems.add<ChildSystem>();
    uiFactory.systems.add<DepthSystem>();

    uiFactory.systems.add<MouseInputSystem>();
    uiFactory.systems.add<MouseEventDispatcherSystem>();

    uiFactory.systems.add<ButtonSystem>();

    uiFactory.systems.add<SizeSystem>();
    uiFactory.systems.add<ScaleSystem>();
    uiFactory.systems.add<RotationSystem>();

    // Layouts
    uiFactory.systems.add<LayoutSystem>();

    uiFactory.systems.add<StackSystem>();
    uiFactory.systems.add<ScrollViewerSystem>();
    uiFactory.systems.add<PositionSystem>();



    uiFactory.systems.add<RenderFrameSystem>();
    uiFactory.systems.add<RenderSystem>(graphics);


    uiFactory.systems.configure();


    spriteAnimationFactory.systems.add<KeyInputSystem>();
    spriteAnimationFactory.systems.add<MoveCommandSystem>();


    spriteAnimationFactory.systems.add<MoveCharacterSystem>();
    spriteAnimationFactory.systems.add<SpriteAnimationSystem>();
    spriteAnimationFactory.systems.add<SpritePositionSystem>();
    spriteAnimationFactory.systems.add<SpriteRenderSystem>(graphics);
    spriteAnimationFactory.systems.configure();
}

void Inanna::WindowManager::Update(entityx::TimeDelta dt) {
    uiFactory.systems.update<ChildSystem>(dt);
    uiFactory.systems.update<DepthSystem>(dt);

    uiFactory.systems.update<MouseInputSystem>(dt);
    uiFactory.systems.update<MouseEventDispatcherSystem>(dt);

    uiFactory.systems.update<ButtonSystem>(dt);

    uiFactory.systems.update<StackSystem>(dt);
    uiFactory.systems.update<ScrollViewerSystem>(dt);


    uiFactory.systems.update<SizeSystem>(dt);
    uiFactory.systems.update<ScaleSystem>(dt);
    uiFactory.systems.update<RotationSystem>(dt);

    uiFactory.systems.update<LayoutSystem>(dt);

    uiFactory.systems.update<PositionSystem>(dt);




    uiFactory.systems.update<RenderFrameSystem>(dt);
    uiFactory.systems.update<RenderSystem>(dt);


    spriteAnimationFactory.systems.update<KeyInputSystem>(dt);
    spriteAnimationFactory.systems.update<MoveCommandSystem>(dt);
    spriteAnimationFactory.systems.update<MoveCharacterSystem>(dt);
    spriteAnimationFactory.systems.update<SpriteAnimationSystem>(dt);
    spriteAnimationFactory.systems.update<SpritePositionSystem>(dt);
    spriteAnimationFactory.systems.update<SpriteRenderSystem>(dt);
}

void Inanna::WindowManager::Test(SDL_Keycode code) {
#ifdef WINDOW_MANAGER_TEST
    switch (code) {
        case SDLK_y: {

            auto nativeSize = Vecf(Resources::FIELDS.TENNIS_FIELD2.w, Resources::FIELDS.TENNIS_FIELD2.h) * 1.5f;
            auto centerPos = (Vecf(SCREEN_WIDTH, SCREEN_HEIGHT) - nativeSize) * 0.5f;
            entityx::Entity parent = uiFactory.CreateCanvas(centerPos, nativeSize);
            entityx::Entity stack = uiFactory.CreateStack(DirectionType::Vertical);
            entityx::Entity scrollViewer = uiFactory.CreateScrollViewer(DirectionType::Vertical, Vecf(0, 0), Vecf(400, 600));
            entityx::Entity child = uiFactory.CreateCanvas();

            parent.assign<Root>();
            parent.assign<RenderFrame>(Rectf(Vecf(0, 0), nativeSize));
            parent.component<Renderable>()->target = Resources::FIELDS.TENNIS_FIELD2;
            parent.assign<MouseClick>([](entityx::Entity entity, SDL_MouseButtonEvent event) {
                printf("MouseClick %s\n", entity.component<Renderable>()->target.id);
            });


//            child.component<Renderable>()->target = Resources::PIECES.RED;
            auto button = child.assign<Button>();
            button->SetStateAsset(ButtonState::Idle, Resources::PIECES.RED)
                    ->SetStateAsset(ButtonState::Over, Resources::PIECES.YELLOW)
                    ->SetStateAsset(ButtonState::Disable, Resources::PIECES.GREEN)
                    ->SetStateAsset(ButtonState::Pressed, Resources::PIECES.DARK_PURPLE);
            child.assign<MouseClick>([](entityx::Entity entity, SDL_MouseButtonEvent event) {
                printf("MouseClick %s\n", entity.component<Renderable>()->target.id);
            });


            std::pair<LayoutType, float> center = {LayoutType::LT_CENTER, 0};
            scrollViewer.assign<Layout>(center);
            std::pair<LayoutType, float> hCenter = {LayoutType::LT_HORIZONTAL_CENTER, 0};
            stack.assign<Layout>(hCenter);

            uiFactory.events.emit<ChildEvent>(parent, scrollViewer, true);
            uiFactory.events.emit<ChildEvent>(scrollViewer, stack, true);
            uiFactory.events.emit<ChildEvent>(stack, child, true);

            entityx::Entity child1 = uiFactory.CreateCanvas();
            child1.component<Renderable>()->target = Resources::PIECES.GREEN;
            uiFactory.events.emit<ChildEvent>(stack, child1, true);

            entityx::Entity child2 = uiFactory.CreateCanvas();
            child2.component<Renderable>()->target = Resources::PIECES.DARK_PURPLE;
            uiFactory.events.emit<ChildEvent>(stack, child2, true);

            entityx::Entity child3 = uiFactory.CreateCanvas();
            child3.component<Renderable>()->target = Resources::PIECES.DARK_PURPLE;
            uiFactory.events.emit<ChildEvent>(stack, child3, true);

//            entityx::Entity child4 = uiFactory.CreateCanvas();
//            child4.component<Renderable>()->target = Resources::PIECES.DARK_PURPLE;
//            uiFactory.events.emit<ChildEvent>(stack, child4, true);

            entityx::Entity child5 = uiFactory.CreateCanvas();
            child5.component<Renderable>()->target = Resources::PIECES.CYAN;
            uiFactory.events.emit<ChildEvent>(stack, child5, true);


            entityx::Entity child6 = uiFactory.CreateCanvas();
            child6.component<Renderable>()->target = Resources::PIECES.YELLOW;
            uiFactory.events.emit<ChildEvent>(parent, child6, true);

            break;
        }
        case SDLK_p: {
            MouseInput::Instance.PrintKeys();
            break;
        }
        case SDLK_g: {
            graphics->monitorX->ShowEntityEditor(true);
            break;
        }
        case SDLK_c: {
            uiFactory.events.emit<ClearAllEvent>();
            break;
        }
        case SDLK_n: {
            spriteAnimationFactory.character = spriteAnimationFactory.CreateAnimation(AnimationData::KYO_IDLE);
            spriteAnimationFactory.character.assign<Character>("Kyo");
            spriteAnimationFactory.character.assign<UserKeyContainer>();
            spriteAnimationFactory.character.assign<MoveState>();
            break;
        }
        default:
            break;
    }

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

