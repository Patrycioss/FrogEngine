#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"
#include "ImGuiManager.hpp"
#include "GlfwManager.hpp"

void ClearScreen(const ImVec4 &clearColour) {
  glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
  // Initialization
  GLFWwindow *window = GlfwManager::Setup();
  ImGuiManager::Setup(window);
  
  // GL Settings
  glEnable(GL_CULL_FACE);

  ImVec4 clearColour{0.45f, 0.55f, 0.60f, 1.00f};
  
  ShaderProgram shader{"resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"};
  SpriteRenderer spriteRenderer{shader};
  
  Texture& texture = ResourceManager::LoadTexture("resources/textures/awesomeface.png", true);

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
  
  shader.Use();
  shader.SetMatrix4("projection", projection);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
	
    ClearScreen(clearColour);
    ImGuiManager::NewFrame();
	
    // Rendering
	ImGui::Begin("Ha");
	ImGui::SetWindowSize({300, 300});
	ImGui::End();

	spriteRenderer.DrawSprite(texture, {0,0}, {512,512});

    ImGuiManager::PostFrame();
	GlfwManager::PostFrame(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}