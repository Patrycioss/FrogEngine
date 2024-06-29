#pragma once

#include <box2d/box2d.h>
#include <vector>
#include <concepts>
#include <memory>

#include "src/core/Component.hpp"

namespace fe
{
  template<class T, class U>
  concept Derived = std::is_base_of<U, T>::value;

  class Engine;

  /**
   * The base class for all objects in your game.
   */
  class GameObject {

	friend Engine;

	static uint32_t IDs;
	uint32_t ID;
	bool wasRenderedThisFrame;

	std::vector<std::unique_ptr<Component>> components;

	void InternalStart();
	void InternalUpdate(float _deltaTime);
	void InternalRender();

   protected:

	/**
	 * Box2D body in use by the GameObject.
	 */
	b2BodyId body;

	/**
	 * Definition of the shape of the GameObject.
	 * Do note that if you want your sprites to be rendered you need to add a shape to the GameObject.
	 * You can do this either manually or let a component like Sprite or AnimatedSprite do it for you.
	 */
	b2ShapeDef shapeDef;

	/**
	 * Called after the behaviours are added and started.
	 * It is recommended to do initialization of the components in the constructor
	 * via functions or via the component's constructor.
	 */
	virtual void Start() {};

	/**
	 * Called every frame by the engine. 
	 */
	virtual void Update(float _deltaTime) {};

	/**
	 * Called every frame after update is called.
	 */
	virtual void Render() {};

	
   public:

	/**
     * Constructor of the GameObject.
     * @param _b2BodyType The type of the body that the GameObject will make, i.e: static, dynamic, kinematic.
     *@param _position The initial position of the GameObject, defaults to {0,0}. 
     */
	explicit GameObject(b2BodyType _b2BodyType, const b2Vec2& _position = {0,0});

	/**
	 * Destructor of the GameObject.
	 */
	virtual ~GameObject();

	/**
	 * @return The default Shape definition used to make shapes. 
	 */
	b2ShapeDef& GetShapeDef(); 

	/**
	 * @return The position of the GameObject. 
	 */
	[[nodiscard]] b2Vec2 GetPosition() const;

	/**
	 * @return The rotation as a b2Rot of the GameObject. 
	 */
	[[nodiscard]] b2Rot GetRotation() const;

	/**
	 * @return The rotation of the body as an angle in radians. 
	 */
	[[nodiscard]] float GetAngle() const;

	/**
	  * @return The b2BodyId of the body associated with the GameObject. 
	  */
	[[nodiscard]] const b2BodyId& GetBody() const;

	/**
	 * @return The ID of the GameObject. 
	 */
	[[nodiscard]] uint32_t GetID() const;

	/**
	 * Sets the transform of the GameObject.
	 * @param _position The new position as a 2D vector.
	 * @param _angle The new rotation as an angle in radians. 
	 */
	void SetTransform(const b2Vec2& _position, float _angle);

	/**
	 * Sets the transform of the GameObject.
	 * @param _position The new position as a 2D vector.
	 * @param _rotation The new rotation as a b2Rot.
	 */
	void SetTransform(const b2Vec2& _position, const b2Rot& _rotation);

	/**
	 * Sets the position of the GameObject.
	 * @param _position A 2D vector for the new position.
	 */
	void SetPosition(const b2Vec2& _position);

	/**
	 * Sets the rotation of the GameObject.
	 * @param _angle The new rotation as an angle in radians.
	 */
	void SetAngle(float _angle);

	/**
	 * Sets the rotation of the GameObject.
	 * @param _rotation The new rotation as a b2Rot.
	 */
	void SetRotation(const b2Rot& _rotation);

	/**
	 * Adds a Box2D shape to the Body using the shape definition in the GameObject.
	 * @param _polygon The actual shape of the shape :)
	 * @return The b2ShapeId associated with the shape.
	 */
	b2ShapeId AddShape(const b2Polygon& _polygon);

	/**
	 * Adds a Box2D shape to the Body using a custom shape definition.
	 * @param _shapeDef Contains information mostly used for physics simulation.
	 * @param _polygon The actual shape of the shape :)
	 * @return The b2ShapeId associated with the shape.
	 */
	b2ShapeId AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon);

	/**
	 * Add a Component to the GameObject.
	 * @tparam T Type of the Component, has to inherit from Component.
	 * @tparam Args Arguments necessary to construct the Component. This allows for custom constructors.
	 * @return A pointer to the created Component. Do not delete the pointer manually but instead use the RemoveComponent() function. 
	 */
	template<Derived<Component> T, typename... Args>
	T* AddComponent(Args... args) {
	  components.push_back(std::unique_ptr<T>(new T(std::move(args)...)));
	  T* component = (T*)components.back().get();
	  component->gameObject = this;
	  return component;
	}

	/**
	 * Removes the Component from the GameObject.
	 * @param _component The pointer to the Component to remove. 
	 * @return Whether it succeeded in removing it.
	 */
	bool RemoveComponent(Component* _component) {
	  for (int i = (int)components.size() - 1; i >= 0; i--) {
		if (components[i].get() == _component) {
		  components.erase(components.begin() + i);
		  return true;
		}
	  }
	  return false;
	}

	/**
	 * Remove all Components of a specific type from the GameObject.
	 * @tparam T The type of the Components to remove.
	 */
	template<Derived<Component> T>
	void RemoveComponentsOfType() {
	  for (auto iterator = components.begin(); iterator < components.end(); iterator++) {
		T* a = dynamic_cast<T*>(*iterator.base());
		if (a != nullptr) {
		  components.erase(iterator);
		}
	  }
	};

	/**
	 * Gets a Component by type.
	 * @tparam T The type of the Component.
	 * @return A pointer to the found Component. Can be null!
	 */
	template<class T>
	T* GetComponent() {
	  for (auto& component : components) {
		T* a = dynamic_cast<T*>(component.get());
		if (a != nullptr) {
		  return a;
		}
	  }
	  return nullptr;
	};
  };

  inline bool operator==(const GameObject& _left, const GameObject& _right) {
	return _left.GetID() == _right.GetID();
  }
}