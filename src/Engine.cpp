#include "Engine.hpp"
#include "GlfwManager.hpp"
#include "ImGuiManager.hpp"
#include "SpriteRenderer.hpp"
#include "glad/glad.h"

namespace FrogEngine
{
  void Engine::Start() {
	window = GlfwManager::Setup();
	ImGuiManager::Setup(window);

	SpriteRenderer::Initialize();

	glEnable(GL_CULL_FACE);

	float timeStep = 1.0f / 60.0f;

	int32_t velocityIterations = 6;
	int32_t positionIterations = 2;

	OnStart();
	
	double lastTime = glfwGetTime();
	float deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
	  ImGuiManager::NewFrame();

	  double nowTime = glfwGetTime();
	  deltaTime = (float)(nowTime - lastTime);
	  lastTime = nowTime;

	  OnUpdate(deltaTime);

	  for (int32 i = 0; i < 60; ++i) {
		world.Step(timeStep, velocityIterations, positionIterations);
	  }

	  ImGuiManager::PostFrame();
	  GlfwManager::PostFrame(window);
	}

	OnStop();

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