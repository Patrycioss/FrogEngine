#include "Engine.hpp"

#include "ImGuiManager.hpp"
#include "GlfwManager.hpp"
#include "glad/glad.h"

namespace FrogEngine
{
  void Engine::Start(IGame* _game) {

	window = GlfwManager::Setup();
	ImGuiManager::Setup(window);

	glEnable(GL_CULL_FACE);

	float timeStep = 1.0f / 60.0f;

	int32_t velocityIterations = 6;
	int32_t positionIterations = 2;

	_game->Start();

	double lastTime = glfwGetTime();
	float deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
	  ImGuiManager::NewFrame();

	  double nowTime = glfwGetTime();
	  deltaTime = (float)(nowTime - lastTime);
	  lastTime = nowTime;

	  _game->Update(deltaTime);

	  for (int32 i = 0; i < 60; ++i) {
		_game->World.Step(timeStep, velocityIterations, positionIterations);
	  }

	  ImGuiManager::PostFrame();
	  GlfwManager::PostFrame(window);
	}

	_game->Stop();

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