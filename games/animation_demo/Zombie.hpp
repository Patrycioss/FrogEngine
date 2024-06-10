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
   
   void SetState(State _state);
   
  protected:
   void OnUpdate(float _deltaTime) override;
   
  public:
   Zombie();
  };
}