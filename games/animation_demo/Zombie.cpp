#include "Zombie.hpp"

namespace AnimationDemo
{
  Zombie::Zombie(fe::Key _leftKey, fe::Key _rightKey) :
  leftKey(_leftKey), rightKey(_rightKey),
  currentState(State::Standing),
  fe::GameObject(b2_staticBody) {
	
	fe::Texture* texture = fe::ResourceManager::LoadTexture("resources/spritesheets/zombie/sheet.png");
	fe::AnimationSettings animationSettings{9, 5};
	animationSettings.SetCycle(0,1);
	animationSettings.fps = 12;
	sprite = AddComponent<fe::AnimatedSprite>(texture, animationSettings);
  }

  void Zombie::OnUpdate(float _deltaTime) {
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