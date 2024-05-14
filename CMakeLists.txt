cmake_minimum_required(VERSION 3.28)
project(FrogEngine)

set(CMAKE_CXX_STANDARD 23)
set(EXT_LIB_PATH ${CMAKE_SOURCE_DIR}/ext)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${EXT_LIB_PATH}/glm)

add_executable(
        FrogEngine

        ${EXT_LIB_PATH}/glad/src/glad.c

        ${EXT_LIB_PATH}/imgui/src/imgui.cpp
        ${EXT_LIB_PATH}/imgui/src/imgui_demo.cpp
        ${EXT_LIB_PATH}/imgui/src/imgui_draw.cpp
        ${EXT_LIB_PATH}/imgui/src/imgui_tables.cpp
        ${EXT_LIB_PATH}/imgui/src/imgui_widgets.cpp
        ${EXT_LIB_PATH}/imgui/src/imgui_impl_glfw.cpp
        ${EXT_LIB_PATH}/imgui/src/imgui_impl_opengl3.cpp

        main.cpp
        ShaderProgram.cpp
        ResourceManager.hpp
        ResourceManager.cpp
        SpriteRenderer.cpp
        ImGuiManager.hpp
        GlfwManager.hpp
        Texture.cpp
)

find_package(box2d CONFIG REQUIRED)

target_link_libraries(
        FrogEngine PRIVATE

        ${EXT_LIB_PATH}/glfw/libglfw3.a
        ${EXT_LIB_PATH}/box2D/box2d.lib
        glm::glm
)

target_include_directories(
        FrogEngine PRIVATE

        ${EXT_LIB_PATH}/glad/include
        ${EXT_LIB_PATH}/glfw/include
        ${EXT_LIB_PATH}/box2D/include
        ${EXT_LIB_PATH}/imgui/include
        ${EXT_LIB_PATH}/stb/include
        ${EXT_LIB_PATH}/glm
)