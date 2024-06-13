#include "GameDemo.hpp"

namespace GameDemo
{
  GameDemo::GameDemo()
  {
	fe::Engine::SetGravity({0,100});
	fe::Box2DDebug::Enable();
	zombie = Instantiate<Zombie>(fe::Key::A, fe::Key::D);
	zombie->SetPosition({300,300});
	
	
	fe::GameObject* ground = Instantiate<fe::GameObject>(b2_staticBody);
	
	b2Vec2 windowSize = fe::Engine::GetWindowSize();
	
	ground->SetPosition({windowSize.x/2.0f, windowSize.y - 11});
	b2Polygon groundPolygon = b2MakeBox(windowSize.x /2.0f, 20);
	ground->AddShape(groundPolygon);

	staticRect = Instantiate<fe::GameObject>(b2_staticBody);
	staticRect->SetPosition({windowSize.x/2.0f, 90});
	b2Polygon staticPoly = b2MakeBox(30,10);
	staticRect->AddShape(staticPoly);
	
	fe::GameObject* dynamicRect = Instantiate<fe::GameObject>(b2_dynamicBody);
	dynamicRect->SetPosition({windowSize.x/2.0f, 100});
	b2Polygon dynamicPoly = b2MakeBox(5,5);
	dynamicRect->AddShape(dynamicPoly);

	//Todo: make wrecking ball :)
	
	b2DistanceJointDef jointDef = b2DefaultDistanceJointDef();
	jointDef.bodyIdA = staticRect->GetBody();
	jointDef.bodyIdB = dynamicRect->GetBody();
	jointDef.minLength = 0;
	jointDef.maxLength = 100;
	jointDef.collideConnected = false;
	jointDef.enableLimit = true;
	jointDef.dampingRatio = 0;
	jointDef.enableSpring = true;
	b2JointId joint = b2CreateDistanceJoint(fe::Engine::GetWorldId(), &jointDef);
	b2DistanceJoint_EnableSpring(joint,true);
  }

  void GameDemo::Start() {
  }

  void GameDemo::Update(float _deltaTime) {
	if (fe::Input::GetKey(fe::Key::LEFT)){
	  staticRect->SetPosition(staticRect->GetPosition() + b2Vec2{-100 * _deltaTime,0});
	}
	else if (fe::Input::GetKey(fe::Key::RIGHT)){
	  staticRect->SetPosition(staticRect->GetPosition() + b2Vec2{100 * _deltaTime,0});
	}
  }

  void GameDemo::Stop() {

  }
}