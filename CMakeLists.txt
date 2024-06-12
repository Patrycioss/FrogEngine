cmake_minimum_required(VERSION 3.28)
project(FrogEngine)

set(CMAKE_CXX_STANDARD 23)
set(EXT_LIB_PATH ${CMAKE_SOURCE_DIR}/ext)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${EXT_LIB_PATH}/glm)

add_library(box2D STATIC IMPORTED
        games/pong/PongGame.cpp
        games/pong/PongGame.hpp)
SET_TARGET_PROPERTIES(box2D PROPERTIES IMPORTED_LOCATION ${EXT_LIB_PATH}/box2D/libbox2d.a)

add_executable(
        FrogEngine

        ${EXT_LIB_PATH}/glad/src/glad.c

        main.cpp
        
        # components
        src/components/AnimatedSprite.cpp
        src/components/Sprite.cpp

        # core
        src/core/AssetManager.cpp
        src/core/Box2DDebug.cpp
        src/core/Engine.cpp
        src/core/GameObject.cpp
        src/core/Renderer.cpp
        src/core/Time.cpp

        # data
        src/data/Colour.cpp
        src/data/Shader.cpp
        src/data/Texture.cpp

        # fileIO
        src/fileIO/FileUtils.cpp
        
        # input
        src/input/Input.cpp
        
        # pong game
        games/pong/PongGame.cpp
        games/pong/Paddle.cpp
        
        # animation demo
        games/animation_demo/AnimationDemo.cpp
        games/animation_demo/Zombie.cpp

)


target_link_libraries(FrogEngine PRIVATE box2D)

target_link_libraries(
        FrogEngine PRIVATE
        ${EXT_LIB_PATH}/glfw/libglfw3.a
        glm::glm
)

target_include_directories(
        FrogEngine PRIVATE

        ${EXT_LIB_PATH}/glad/include
        ${EXT_LIB_PATH}/glfw/include
        ${EXT_LIB_PATH}/box2D/include
        ${EXT_LIB_PATH}/stb/include
        ${EXT_LIB_PATH}/glm
)