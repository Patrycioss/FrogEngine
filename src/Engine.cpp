#include "Engine.hpp"

#include <glad/glad.h>

//#include "ImGuiManager.hpp"
#include "SpriteRenderer.hpp"

namespace fe
{
  b2World Engine::world{{0, 0}};
  GLFWwindow* Engine::window;
  bool Engine::initCalled = false;
  Settings Engine::currentSettings{};
  Camera Engine::camera{};
  
  const Settings& Engine::CurrentSettings = Engine::currentSettings;
  const Camera& Engine::Camera = Engine::camera;

  void Engine::Initialize(GameTemplate& _gameTemplate) {
	if (initCalled) {
	  throw std::runtime_error("Initialize has already been called before!");
	}

	initCalled = true;
	currentSettings = _gameTemplate.Settings;

	glfwInit();
	window = glfwCreateWindow(currentSettings.windowWidth, currentSettings.windowHeight, currentSettings.windowTitle, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//vsync
	glfwSwapInterval(currentSettings.enableVsync); // Enable: 1, Disable: 0

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//face culling
	if (currentSettings.enableFaceCulling) {
	  glEnable(GL_CULL_FACE);
	} else {
	  glDisable(GL_CULL_FACE);
	}

	glfwShowWindow(window);

	SpriteRenderer::Initialize();
//	float timeStep = 1.0f / 60.0f;
//	int32_t velocityIterations = 6;
//	int32_t positionIterations = 2;

	_gameTemplate.Start();

	double lastTime = glfwGetTime();
	float deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
//	  ImGuiManager::NewFrame();

	  double nowTime = glfwGetTime();
	  deltaTime = (float)(nowTime - lastTime);
	  lastTime = nowTime;

	  _gameTemplate.Update(deltaTime);

//	  for (int32 i = 0; i < 60; ++i) {
//		world.Step(timeStep, velocityIterations, positionIterations);
//	  }

	  int display_w, display_h;
	  glfwGetFramebufferSize(window, &display_w, &display_h);
	  glad_glViewport(0, 0, display_w, display_h);

	  glfwSwapBuffers(window);

//	  ImGuiManager::PostFrame();
//	  GlfwManager::PostFrame(window);
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

  void Engine::ApplyAllSettings(const Settings& _settings) {
	currentSettings = _settings;

	glfwSwapInterval(currentSettings.enableVsync); // Enable: 1, Disable: 0

	if (currentSettings.enableFaceCulling) {
	  glEnable(GL_CULL_FACE);
	} else {
	  glDisable(GL_CULL_FACE);
	}

	glfwSetWindowSize(window, currentSettings.windowWidth, currentSettings.windowHeight);
	glfwSetWindowTitle(window, currentSettings.windowTitle);
  }

  void Engine::ApplySettings(const Settings& _settings, uint16_t _flags) {
	if ((_flags & Settings::VSYNC) == Settings::VSYNC) {
	  currentSettings.enableVsync = _settings.enableVsync;
	  glfwSwapInterval(currentSettings.enableVsync); // Enable: 1, Disable: 0
	}

	if ((_flags & Settings::CULL_FACE) == Settings::CULL_FACE) {
	  currentSettings.enableFaceCulling = _settings.enableFaceCulling;
	  if (currentSettings.enableFaceCulling) {
		glEnable(GL_CULL_FACE);
	  } else {
		glDisable(GL_CULL_FACE);
	  }
	}

	if ((_flags & Settings::WINDOW_SIZE) == Settings::WINDOW_SIZE) {
	  currentSettings.windowWidth = _settings.windowWidth;
	  currentSettings.windowHeight = _settings.windowHeight;
	  glfwSetWindowSize(window, currentSettings.windowWidth, currentSettings.windowHeight);
	}

	if ((_flags & Settings::WINDOW_TITLE) == Settings::WINDOW_TITLE) {
	  currentSettings.windowTitle = _settings.windowTitle;
	  glfwSetWindowTitle(window, currentSettings.windowTitle);
	}
  }
}