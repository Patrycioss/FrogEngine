#include "PhysicsDemo.hpp"
#include "MovablePlatform.hpp"

namespace PhysicsDemo
{
  PhysicsDemo::PhysicsDemo() {
	fe::Engine::SetGravity({0, 100});
	fe::Box2DDebug::Enable();

	b2Vec2 windowSize = fe::Engine::GetWindowSize();

	// Ground
	{
	  fe::GameObject* ground = Instantiate<fe::GameObject>(b2_staticBody, b2Vec2{windowSize.x / 2.0f, windowSize.y - 11});
	  b2Polygon groundPolygon = b2MakeBox(windowSize.x / 2.0f, 20);
	  ground->AddShape(groundPolygon);
	}

	b2BodyId bodyId = Instantiate<MovablePlatform>(b2Vec2{300,200})->GetBody();
	
	Rope rope(bodyId, b2Vec2(0, 5), 10, 10, 30);
	Instantiate<Zombie>(fe::Key::A, fe::Key::D, b2Vec2{400, 500});

	b2Polygon horBoundBox = b2MakeBox(windowSize.x / 2.0f, 5);
	b2Polygon vertBoundBox = b2MakeBox(5, windowSize.y / 2.0f);

	// LBound
	{
	  fe::GameObject* leftBound = Instantiate<fe::GameObject>(b2_staticBody, b2Vec2{0, windowSize.y / 2.0f});
	  leftBound->AddShape(vertBoundBox);
	}

	// RBound
	{
	  fe::GameObject* rightBound = Instantiate<fe::GameObject>(b2_staticBody, b2Vec2{windowSize.x, windowSize.y / 2.0f});
	  rightBound->AddShape(vertBoundBox);
	}

	// CeilingBound
	{
	  fe::GameObject* ceilingBound = Instantiate<fe::GameObject>(b2_staticBody, b2Vec2{windowSize.x / 2.0f, 0});
	  ceilingBound->AddShape(horBoundBox);
	}
  }

  void PhysicsDemo::Start() {

  }

  void PhysicsDemo::Update(float _deltaTime) {

  }

  void PhysicsDemo::Stop() {

  }
}