#include "MovablePlatform.hpp"

namespace PhysicsDemo
{
  void MovablePlatform::Update(float _deltaTime) {
	if (fe::Input::GetKey(fe::Key::DOWN)){
	  b2Body_ApplyForceToCenter(body,{0,FORCE}, true);
	}

	if (fe::Input::GetKey(fe::Key::UP)){
	  b2Body_ApplyForceToCenter(body,{0,-FORCE}, true);
	}
	if (fe::Input::GetKey(fe::Key::LEFT)){
	  b2Body_ApplyForceToCenter(body,{-FORCE,0}, true);
	}
	if (fe::Input::GetKey(fe::Key::RIGHT)){
	  b2Body_ApplyForceToCenter(body,{FORCE,0}, true);
	}
  }

  MovablePlatform::MovablePlatform(b2Vec2 _position) : fe::GameObject(b2_dynamicBody, _position) {

	fe::Texture* texture = fe::AssetManager::LoadTexture("resources/textures/brown_square.png");
	AddComponent<fe::Sprite>(texture, false, b2Vec2{60,20});

	b2Body_SetFixedRotation(body,true);
	b2Body_SetGravityScale(body,0);

	shapeDef.friction = 1.0f;
	shapeDef.density = 1.0f;
	
	b2Polygon staticPoly = b2MakeBox(30,10);
	AddShape(staticPoly);
  }
} // PhysicsDemo