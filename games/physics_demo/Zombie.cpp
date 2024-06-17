#include "Zombie.hpp"

namespace PhysicsDemo
{
  Zombie::Zombie(fe::Key _leftKey, fe::Key _rightKey, b2Vec2 _position) :
  leftKey(_leftKey), rightKey(_rightKey),
  currentState(State::Standing),
  fe::GameObject(b2_dynamicBody, _position) {
	
	
	fe::Texture* texture = fe::AssetManager::LoadTexture("resources/spritesheets/zombie/sheet.png");
	fe::AnimationSettings animationSettings{9, 5};
	
	animationSettings.SetCycle(0,1);
	animationSettings.fps = 12;
	sprite = AddComponent<fe::AnimatedSprite>(texture, animationSettings, false);
	
	b2Polygon polygon = b2MakeOffsetBox(37, 52, {0,12}, 0);
	shapeDef.friction = 0.5f;
	shapeDef.density = 100;
	b2Body_SetFixedRotation(body,true);
	AddShape(polygon);
	
	
	b2MassData massData{};
	massData.mass = 100;
	b2Body_SetMassData(body, massData);
  }

  void Zombie::Update(float _deltaTime) {
//	printf("mass: %f \n", b2Body_GetMass(body));
	
	if (fe::Input::GetKey(rightKey)){
	  sprite->FlipHorizontal(false);
	  SetState(State::Walking);
	  b2Body_ApplyForceToCenter(body, {20000,0}, true);
//	  b2Body_ApplyLinearImpulseToCenter(body, b2Vec2{200,0} * _deltaTime, true);
//	  SetPosition(GetPosition() + b2Vec2{150 * _deltaTime,0});
	}
	else if (fe::Input::GetKey(leftKey)){
	  sprite->FlipHorizontal(true);
	  SetState(State::Walking);
	  b2Body_ApplyForceToCenter(body, {-20000,0}, true);
//	  b2Body_ApplyLinearImpulseToCenter(body, b2Vec2{-2000,0} * _deltaTime, true);
//	  SetPosition(GetPosition() - b2Vec2{150 * _deltaTime,0});
	}
	else{
	  SetState(State::Standing);
	}

	if (fe::Input::GetKeyDown(fe::Key::SPACE)){
	  b2Body_ApplyForceToCenter(body, {0,-2000000}, true);
	}
  }

  void Zombie::SetState(Zombie::State _state) {
	switch (_state){
	  case State::Walking:
		if (currentState == State::Walking){
		  return;
		}
		
		sprite->SetCycle(36,8);
		break;
	  
	  case State::Standing:
		if (currentState == State::Standing){
		  return;
		}
		
		sprite->SetCycle(0,1);
		break;
	}
	
	currentState = _state;
  }
}