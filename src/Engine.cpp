#include "Engine.hpp"

#include <glad/glad.h>

#include "GlfwManager.hpp"
#include "ImGuiManager.hpp"
#include "SpriteRenderer.hpp"

namespace fe
{
  b2World Engine::world{{0, 0}};
  GLFWwindow* Engine::window;

  void Engine::Init(GameTemplate& _gameTemplate) {
	window = GlfwManager::Setup();
	ImGuiManager::Setup(window);

	SpriteRenderer::Initialize();

	glEnable(GL_CULL_FACE);

	float timeStep = 1.0f / 60.0f;

	int32_t velocityIterations = 6;
	int32_t positionIterations = 2;

	_gameTemplate.Start();

	double lastTime = glfwGetTime();
	float deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
	  ImGuiManager::NewFrame();

	  double nowTime = glfwGetTime();
	  deltaTime = (float)(nowTime - lastTime);
	  lastTime = nowTime;

	  _gameTemplate.Update(deltaTime);

	  for (int32 i = 0; i < 60; ++i) {
		world.Step(timeStep, velocityIterations, positionIterations);
	  }

	  ImGuiManager::PostFrame();
	  GlfwManager::PostFrame(window);

	}

	_gameTemplate.Stop();

	SpriteRenderer::Cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();
  }

  void Engine::Stop() {
	if (!glfwWindowShouldClose(window)) {
	  glfwSetWindowShouldClose(window, true);
	  return;
	}
  }
}