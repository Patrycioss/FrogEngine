#include <box2d/box2d.h>
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
  
  b2Vec2 gravity{0.0f, -10.0f};
  b2World world{gravity};
  
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);
  
  b2Body* groundBody = world.CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);

  groundBody->CreateFixture(&groundBox, 0.0f);

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  b2Body* body = world.CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  body->CreateFixture(&fixtureDef);

  float timeStep = 1.0f / 60.0f;

  int32 velocityIterations = 6;
  int32 positionIterations = 2;


  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    for (int32 i = 0; i < 60; ++i)
    {
	  world.Step(timeStep, velocityIterations, positionIterations);
	  b2Vec2 position = body->GetPosition();
	  float angle = body->GetAngle();
	  printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }


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