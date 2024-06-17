#include "AnimationDemo.hpp"

namespace AnimationDemo
{
  AnimationDemo::AnimationDemo()
  {
	b2World_SetHitEventThreshold(fe::Engine::GetWorldId(), 10);
	
	fe::Engine::SetGravity({0,100});
	fe::Box2DDebug::Enable();
	zombie = Instantiate<Zombie>(fe::Key::A, fe::Key::D);
	zombie->SetPosition({300,300});
	
	
	fe::GameObject* ground = Instantiate<fe::GameObject>(b2_staticBody);
	
	b2Vec2 windowSize = fe::Engine::GetWindowSize();
	
	ground->SetPosition({windowSize.x/2.0f, windowSize.y - 11});
	b2Polygon groundPolygon = b2MakeBox(windowSize.x /2.0f, 20);
	ground->AddShape(groundPolygon);
  }

  void AnimationDemo::Start() {
  }

  void AnimationDemo::Update(float _deltaTime) {
  }

  void AnimationDemo::Stop() {

  }
}