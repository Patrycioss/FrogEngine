
#https://dominikberner.ch/cmake-library-setup/

cmake_minimum_required(VERSION 3.28)
project(
        FrogEngine
        VERSION 1.0.0
        DESCRIPTION
            "A 2D game engine with built-in Box2D support"
        LANGUAGES CXX
)

set(EXT_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext)




# External libraries
add_subdirectory(${EXT_LIB_PATH}/glm)

add_library(box2D STATIC IMPORTED)
SET_TARGET_PROPERTIES(box2D PROPERTIES IMPORTED_LOCATION ${EXT_LIB_PATH}/box2D/libbox2d.a)

add_library(glfw STATIC IMPORTED)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION ${EXT_LIB_PATH}/glfw/libglfw3.a)

add_library(glad ${EXT_LIB_PATH}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${EXT_LIB_PATH}/glad/include)

# FrogEngine Library
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(FrogEngine ${SOURCES})
target_compile_definitions(FrogEngine PRIVATE ENGINE_RESOURCES="${CMAKE_CURRENT_BINARY_DIR}/resources")

set_target_properties(
        FrogEngine
        PROPERTIES VERSION ${PROJECT_VERSION}
                    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_link_libraries(
        FrogEngine

        glad
        box2D
        glfw
        glm::glm
)


target_include_directories(
        FrogEngine
        PUBLIC src

        ${EXT_LIB_PATH}/glfw/include
        ${EXT_LIB_PATH}/box2D/include
        ${EXT_LIB_PATH}/stb/include
        ${EXT_LIB_PATH}/glm
)