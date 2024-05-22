#include "Scene.hpp"

namespace fe
{
  void Scene::Start() {
	for (auto& object : objects) {
	  object->Start();
	}
  }

  void Scene::Update(float _deltaTime) {
	for (auto& object : objects) {
	  object->Update(_deltaTime);
	}
  }

  bool Scene::RemoveObject(GameObject& _object) {
	for (int i = (int)objects.size(); i >= 0; i--) {
	  if (*objects[i] == _object) {
		objects.erase(objects.begin() + i);
		return true;
	  }
	}

	return false;
  }

  Scene::~Scene() {
	for (int i = (int)objects.size() - 1; i >= 0; i--) {
	  delete objects[i];
	}
  }
}