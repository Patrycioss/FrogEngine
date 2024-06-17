#include "Zombie.hpp"

namespace AnimationDemo
{
  Zombie::Zombie(fe::Key _leftKey, fe::Key _rightKey) :
  leftKey(_leftKey), rightKey(_rightKey),
  currentState(State::Standing),
  fe::GameObject(b2_dynamicBody) {
	
	
	fe::Texture* texture = fe::AssetManager::LoadTexture("resources/spritesheets/zombie/sheet.png");
	fe::AnimationSettings animationSettings{9, 5};
	
	animationSettings.SetCycle(0,1);
	animationSettings.fps = 12;
	sprite = AddComponent<fe::AnimatedSprite>(texture, animationSettings, false);
	
	b2Polygon polygon = b2MakeOffsetBox(37, 52, {0,12}, 0);
	shapeDef.friction = 0;
	shapeDef.density = 1;
	AddShape(polygon);

	
  }

  void Zombie::Update(float _deltaTime) {
	if (fe::Input::GetKey(rightKey)){
	  sprite->FlipHorizontal(false);
	  SetState(State::Walking);
	  SetPosition(GetPosition() + b2Vec2{150 * _deltaTime,0});
	}
	else if (fe::Input::GetKey(leftKey)){
	  sprite->FlipHorizontal(true);
	  SetState(State::Walking);
	  SetPosition(GetPosition() - b2Vec2{150 * _deltaTime,0});
	}
	else{
	  SetState(State::Standing);
	}

	if (fe::Input::GetKeyDown(fe::Key::SPACE)){
	  b2Body_ApplyForceToCenter(body, {0,-2000000000}, true);
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