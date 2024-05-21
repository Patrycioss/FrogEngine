#pragma once

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <glm.hpp>
#include <imgui.h>
#include <box2d/box2d.h>

#include "Engine.hpp"
#include "SpriteRenderer.hpp"
#include "Shader.hpp"
#include "GameObject.hpp"

namespace FrogEngine
{
  void ClearScreen(const glm::vec4& _clearColour);
}