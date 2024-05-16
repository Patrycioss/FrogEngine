#pragma once

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <glm.hpp>
#include <imgui.h>
#include <box2d/box2d.h>

#include "ResourceManager.hpp"
#include "Engine.hpp"
#include "Shader.hpp"
#include "SpriteRenderer.hpp"

namespace FrogEngine
{
  void ClearScreen(const glm::vec4& _clearColour);
}