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

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${BOX2D_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        src)

add_executable(Inanna main.cpp Assets/Resources.h Assets/Resources.cpp)


target_link_libraries(Inanna ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${OPENGL_gl_LIBRARY}
        ${GLUT_glut_LIBRARY}
        ${GLEW_LIBRARY}
        ${BOX2D_LIBRARY}
        )