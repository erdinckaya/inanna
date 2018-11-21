cmake_minimum_required(VERSION 3.12)
project(Inanna)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(BOX2D REQUIRED)
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

add_executable(Inanna main.cpp Assets/Resources.h Assets/Resources.cpp Server/GameServer.cpp Server/GameServer.h Server/GameAdapter.cpp Server/GameAdapter.h Server/GameChannel.h Server/GameConnectionConfig.h Server/GameMessageFactory.h Server/GameMessageType.h Server/MyMessage.h Base/World.cpp Base/World.h Base/UI/WindowManager.cpp Base/UI/WindowManager.h Base/Graphics/Graphics.cpp Base/Graphics/Graphics.h Base/Graphics/SDL.cpp Base/Graphics/SDL.h Base/Graphics/SDLWindow.cpp Base/Graphics/SDLWindow.h Base/Graphics/SDLContext.cpp Base/Graphics/SDLContext.h Base/Graphics/SDLSurface.cpp Base/Graphics/SDLSurface.h Base/Test/GraphicsTest.h Base/Time/Time.cpp Base/Time/Time.h Base/Util/Math/Vec2.h Base/Util/Math/Rect.h)


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