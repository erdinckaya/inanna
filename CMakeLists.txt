cmake_minimum_required(VERSION 3.12)
project(Inanna)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

add_compile_definitions(WINDOW_MANAGER_TEST START_WORLD MONITORX_DEBUG)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(BOX2D REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
find_package(Glut REQUIRED)
find_package(Entityx REQUIRED)
find_package(flatbuffers REQUIRED)
find_package(Yojimbo REQUIRED)
find_package(Mbedtls REQUIRED)
find_package(Sodium REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${BOX2D_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${ENTITYX_INCLUDE_DIR}
        ${FLATBUFFERS_INCLUDE_DIR}
        ${MBEDTLS_INCLUDE_DIRS}
        ${SODIUM_INCLUDE_DIR})


add_executable(Inanna main.cpp Assets/Resources.h Assets/Resources.cpp Assets/AnimationData.h Assets/AnimationData.cpp
        Server/GameServer.cpp
        Server/GameServer.h Server/GameAdapter.cpp Server/GameAdapter.h Server/GameChannel.h
        Server/GameConnectionConfig.h Server/GameMessageFactory.h Server/GameMessageType.h
        Server/MyMessage.h Base/World.cpp Base/World.h Base/UI/WindowManager.cpp Base/UI/WindowManager.h
        Base/Graphics/Graphics.cpp Base/Graphics/Graphics.h Base/Graphics/SDL.cpp Base/Graphics/SDL.h
        Base/Graphics/SDLWindow.cpp Base/Graphics/SDLWindow.h Base/Graphics/SDLContext.cpp Base/Graphics/SDLContext.h
        Base/Graphics/SDLSurface.cpp Base/Graphics/SDLSurface.h Base/Test/GraphicsTest.h
        Base/Util/Math/Vec2.h Base/Util/Math/Rect.h Base/UI/Systems/RenderSystem.h
        Base/UI/Components/Renderable.h Base/UI/Components/Scalable.h Base/UI/Systems/ScaleSystem.h
        Base/UI/Components/Position.h Base/UI/Systems/PositionSystem.h Base/UI/Components/Sizable.h
        Base/UI/Systems/SizeSystem.h Base/UI/Components/Rotation.h Base/UI/Systems/RotationSystem.h
        Base/UI/Components/Widget.h Base/UI/Components/Root.h Base/UI/Events/ChildEvent.h Base/UI/Systems/ChildSystem.h
        Base/UI/Systems/DepthSystem.h Base/UI/Components/MouseButton.h Base/UI/Components/MouseMotion.h
        Base/UI/Components/MouseWheel.h Base/UI/Systems/MouseInputSystem.h Base/UI/Events/ClearAllEvent.h
        Base/UI/Components/Interaction.h Base/UI/Systems/MouseEventDispatcherSystem.h
        Base/UI/MouseEventComponents/MouseDown.h Base/UI/MouseEvents/MouseUpEvent.h
        Base/UI/MouseEventComponents/MouseUp.h Base/UI/Types.h Base/UI/MouseEventComponents/MouseClick.h
        Base/UI/MouseEvents/MouseClickEvent.h Base/UI/MouseEvents/MouseDragEvent.h
        Base/UI/MouseEventComponents/MouseDrag.h Base/UI/MouseEvents/MouseDragStartEvent.h
        Base/UI/MouseEvents/MouseDragEndEvent.h Base/UI/MouseEventComponents/MouseDragStart.h
        Base/UI/MouseEventComponents/MouseDragEnd.h Base/UI/UIFactory.cpp Base/UI/UIFactory.h
        Base/UI/Widgets/Canvas.h Base/Input/KeyInput.cpp Base/Input/KeyInput.h Base/UI/Widgets/Button.h
        Base/UI/Systems/ButtonSystem.h Base/Input/MouseInput.cpp Base/Input/MouseInput.h
        Base/UI/Components/Layout.h Base/UI/Systems/LayoutSystem.h Base/UI/Widgets/Stack.h
        Base/UI/Systems/StackSystem.h Base/UI/Components/RenderFrame.h Base/UI/Systems/RenderFrameSystem.h
        Base/UI/Widgets/ScrollViewer.h Base/UI/Systems/ScrollViewerSystem.h Base/UI/Widgets/ScrollBar.h
        ThirdParty/MonitorX/3rdParty/ImGui/imconfig.h ThirdParty/MonitorX/3rdParty/ImGui/imgui.cpp
        ThirdParty/MonitorX/3rdParty/ImGui/imgui.h ThirdParty/MonitorX/3rdParty/ImGui/imgui_demo.cpp
        ThirdParty/MonitorX/3rdParty/ImGui/imgui_draw.cpp ThirdParty/MonitorX/3rdParty/ImGui/imgui_impl_opengl2.cpp
        ThirdParty/MonitorX/3rdParty/ImGui/imgui_impl_opengl2.h ThirdParty/MonitorX/3rdParty/ImGui/imgui_impl_sdl.cpp
        ThirdParty/MonitorX/3rdParty/ImGui/imgui_impl_sdl.h ThirdParty/MonitorX/3rdParty/ImGui/imgui_internal.h
        ThirdParty/MonitorX/3rdParty/ImGui/imgui_widgets.cpp ThirdParty/MonitorX/3rdParty/ImGui/imstb_rectpack.h
        ThirdParty/MonitorX/3rdParty/ImGui/imstb_textedit.h ThirdParty/MonitorX/3rdParty/ImGui/imstb_truetype.h
        ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h ThirdParty/MonitorX/3rdParty/FlexibleReflection/Primitives.cpp
        ThirdParty/MonitorX/MonitorX.h ThirdParty/MonitorX/MonitorX.cpp Base/MonitorX/MonitorComponents.cpp
        Base/SpriteAnimation/SpriteAnimationFactory.cpp Base/SpriteAnimation/SpriteAnimationFactory.h
        Base/SpriteAnimation/Components/SpriteAnimation.h Base/SpriteAnimation/Systems/SpriteAnimationSystem.h
        Base/SpriteAnimation/Components/SpriteAnimationState.h Base/SpriteAnimation/Systems/SpritePositionSystem.h
        Base/SpriteAnimation/Systems/SpriteRenderSystem.h Base/Game/Components/Character.h Base/Game/Components/MoveCharacter.h
        Base/Game/Systems/MoveCharacterSystem.h Base/Game/Systems/KeyInputSystem.h
        Base/Util/SpriteMacro.h Base/SpriteAnimation/Components/Time.h
        ThirdParty/Signals/Delegate.h ThirdParty/Signals/Signal.h Base/Game/Command/Components/CommandLink.h Base/Util/CircularBuffer.h Base/Game/Util/GameKey.h Base/Game/Components/UserKey.h Base/Game/Components/UserKeyHistory.h Base/Game/Command/Components/MoveCommand.h Base/Game/Command/Systems/MoveCommandSystem.h Base/Game/Command/Components/HitCommand.h Base/Game/Command/Systems/HitCommandSystem.h Base/Game/Components/Hit.h Base/Game/Systems/HitSystem.h ThirdParty/json.h Base/Game/Game.cpp Base/Game/Game.h Base/Game/Util/KeyPatterns.h Base/Game/Util/SpecialMoveKeyData.h Base/Game/Util/SpecialMoveKey.h Base/Game/Command/Components/CrouchCommand.h Base/Game/Command/Systems/CrouchCommandSystem.h Base/Game/Components/Crouch.h Base/Game/Systems/CrouchSystem.h Base/Game/Command/Components/JumpCommand.h Base/Game/Command/Systems/JumpCommandSystem.h Base/Game/Components/JumpCharacter.h Base/Game/Systems/JumpCharacterSystem.h Base/SpriteAnimation/Event/SpriteIndex.h Base/Game/Events/JumpEnd.h Base/SpriteAnimation/Event/SpriteAnimEnd.h Base/Game/Util/Chrono.h ThirdParty/enum.h Base/Game/Command/Components/JumpBackCommand.h Base/Game/Command/Systems/JumpBackCommandSystem.h Base/Game/Components/JumpBack.h Base/Game/Events/JumpBackEnd.h Base/Game/Systems/JumpBackSystem.h Base/Game/Command/Components/RunCommand.h Base/Game/Command/Systems/RunCommandSystem.h Base/Game/Events/RunEnd.h Base/Game/Components/Run.h Base/Game/Systems/RunSystem.h Base/SpriteAnimation/Components/SpriteLoop.h Base/Game/Command/Components/RollCommand.h Base/Game/Command/Systems/RollCommandSystem.h Base/Game/Components/Roll.h Base/Game/Events/RollEnd.h Base/Game/Systems/RollSystem.h Base/Game/Events/MoveEnd.h Base/Game/Events/CrouchEnd.h Base/Game/Events/LockInput.h Base/Game/Command/Components/OryuCommand.h Base/Game/Command/Systems/OryuCommandSystem.h Base/Game/Components/Oryu.h Base/Game/Events/OryuEnd.h Base/Game/Systems/OryuSystem.h Base/SpriteAnimation/Systems/SpriteGizmoSystem.h Base/Game/Components/Facing.h Base/SpriteAnimation/Systems/SpriteFacingSystem.h Base/Game/Util/CharacterBehaivour.h Base/Game/Components/CharacterState.h Base/Game/Events/AbortEvent.h Base/Game/Systems/KeyInputSystem.cpp Base/Util/Math/Physics.cpp Base/Util/Math/Physics.h Base/Game/Events/HitEnd.h Base/SpriteAnimation/Event/SpriteForceKeyFrame.h Base/SpriteAnimation/Components/SpriteZ.h Base/Game/Command/Components/DamageReceiveCommand.h Base/Game/Command/Systems/DamageCommandSystem.h Base/Game/Components/Damage.h Base/Game/Components/Health.h Base/Game/Systems/DamageSystem.h Base/Game/Events/DamageEnd.h Base/Game/Components/Collidable.h Base/Game/Systems/CollisionSystem.h Base/Game/Events/CollisionEvent.h Base/Game/Components/Gizmo.h)


target_link_libraries(Inanna ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${OPENGL_gl_LIBRARY}
        ${GLUT_glut_LIBRARY}
        ${GLEW_LIBRARY}
        ${BOX2D_LIBRARY}
        ${ENTITYX_LIBRARY}
        ${FLATBUFFERS_LIBRARY}
        ${YOJIMBO_LIBRARY}
        ${MBEDTLS_LIBRARIES}
        ${SODIUM_LIBRARY}
        )