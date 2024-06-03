#include "Engine.hpp"

#include <glad/glad.h>

//#include "ImGuiManager.hpp"
#include "SpriteRenderer.hpp"

namespace fe
{
  Engine::State Engine::state;
  b2WorldId Engine::world;
  b2WorldDef Engine::worldDef = b2DefaultWorldDef();
  GLFWwindow* Engine::window;
  Settings Engine::currentSettings{};
  Camera Engine::camera{};
  std::unordered_map<int32_t, std::unique_ptr<GameObject>> Engine::objectRegistry;

  const Settings& Engine::CurrentSettings = Engine::currentSettings;
  const Camera& Engine::Camera = Engine::camera;
  b2WorldId& Engine::World = Engine::world;

  void Engine::Initialize() {
	if (state != State::None) {
	  throw std::runtime_error("Engine has already been initialized!");
	}

	state = State::Initialize;

	worldDef.gravity = currentSettings.gravity;

	world = b2CreateWorld(&worldDef);

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
  }

  void Engine::Start(GameTemplate& _gameTemplate) {

	if (state == State::None) {
	  throw std::runtime_error("Can't start the engine without initializing first!");
	}

	if (state == State::Start) {
	  throw std::runtime_error("Engine has already started!");
	}

	state = State::Start;

	float timeStep = 1.0f / 60.0f;
	int subStepCount = 4;

	_gameTemplate.Start();
	for (const auto& a : objectRegistry) {
	  a.second->Start();
	}

	double lastTime = glfwGetTime();
	float deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
//	  ImGuiManager::NewFrame();

	  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);              // background color
	  glClear(GL_COLOR_BUFFER_BIT);

	  double nowTime = glfwGetTime();
	  deltaTime = (float)(nowTime - lastTime);
	  lastTime = nowTime;

	  b2World_Step(world, timeStep, subStepCount);

	  _gameTemplate.Update(deltaTime);
	  for (auto& a : objectRegistry) {
		a.second->Update(deltaTime);
	  }

	  // Render
	  b2World_OverlapAABB(world,
						  {{0, 0}, {(float)currentSettings.windowWidth, (float)currentSettings.windowHeight}},
						  b2DefaultQueryFilter(),
						  &ScreenQueryCallback,
						  nullptr);

	  int display_w, display_h;
	  glfwGetFramebufferSize(window, &display_w, &display_h);
	  glad_glViewport(0, 0, display_w, display_h);

	  glfwSwapBuffers(window);

//	  ImGuiManager::PostFrame();
	}

	_gameTemplate.Stop();

	// Always clear objects before destroying world.
	// Otherwise, objects can't clean themselves up properly.
	objectRegistry.clear();
	b2DestroyWorld(world);
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

  b2BodyId Engine::CreateBody(b2BodyDef* _bodyDef) {
	return b2CreateBody(world, _bodyDef);
  }

  void Engine::SetWindowSize(uint16_t _width, uint16_t _height) {
	currentSettings.windowWidth = _width;
	currentSettings.windowHeight = _height;
	glfwSetWindowSize(window, currentSettings.windowWidth, currentSettings.windowHeight);
  }

  void Engine::EnableVsync(bool _enable) {
	currentSettings.enableVsync = _enable;
	glfwSwapInterval(currentSettings.enableVsync); // Enable: 1, Disable: 0
  }

  void Engine::EnableFaceCulling(bool _enable) {
	currentSettings.enableFaceCulling = _enable;
	if (currentSettings.enableFaceCulling) {
	  glEnable(GL_CULL_FACE);
	} else {
	  glDisable(GL_CULL_FACE);
	}
  }

  void Engine::SetWindowTitle(const char* _title) {
	currentSettings.windowTitle = _title;
	glfwSetWindowTitle(window, currentSettings.windowTitle);
  }

  void Engine::SetGravity(b2Vec2 _gravity) {
	currentSettings.gravity = _gravity;
	b2World_SetGravity(world, currentSettings.gravity);
  }

  bool Engine::ScreenQueryCallback(b2ShapeId _shape, void* something) {
	objectRegistry[_shape.index1]->Render();
	return true;
  }

  bool Engine::IsKeyPressed(Key _key) {
	return glfwGetKey(window, (int)_key) == GLFW_PRESS;
  }

  void Engine::Destroy(GameObject* _object) {
	printf("Destroying object with body id: %i \n", _object->GetBody().index1);
	objectRegistry.erase(_object->GetBody().index1);
  }
}