#pragma once

#include <src/FrogEngine.hpp>

namespace AnimationDemo
{
 class Zombie : public fe::GameObject {
  private:
   enum class State{
	 Walking,
	 Standing
   }; 
   
   State currentState;
   fe::AnimatedSprite* sprite;
   
   fe::Key leftKey;
   fe::Key rightKey;
   
   void SetState(State _state);
   
  protected:
   void OnUpdate(float _deltaTime) override;
   
  public:
   Zombie(fe::Key _leftKey, fe::Key _rightKey);
  };
}