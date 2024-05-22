#pragma once

#include <vector>
#include <functional>

#include "GameObject.hpp"

namespace fe
{
  template<class T, class U>
  concept Derived = std::is_base_of<U, T>::value;

  class Scene {
   protected:
	std::vector<GameObject*> objects;

   public:
	const std::vector<GameObject*>& Objects = objects;

	void Start();
	void Update(float _deltaTime);
	bool RemoveObject(GameObject& _object);
	~Scene();

	template<Derived<GameObject> T>
	T* AddObject() {
	  return dynamic_cast<T*>(objects.emplace_back(new T));
	};

	template<Derived<GameObject> T>
	[[nodiscard]] std::vector<T*> GetObjects(const std::function<bool(const T*)>& _predicate) {
	  std::vector<T*> foundObjects{};

	  for (GameObject* object : objects) {
		T* wanted = dynamic_cast<T*>(object);

		if (wanted != nullptr) {
		  if (_predicate(object)) {
			foundObjects.push_back(object);
		  }
		}
	  }

	  return foundObjects;
	}

	template<Derived<GameObject> T>
	[[nodiscard]] std::vector<T*> GetObjects() {
	  std::vector<T*> foundObjects{};

	  for (GameObject* object : objects) {
		T* wanted = dynamic_cast<T*>(object);

		if (wanted != nullptr) {
		  foundObjects.push_back(object);
		}
	  }

	  return foundObjects;
	}
  };
}