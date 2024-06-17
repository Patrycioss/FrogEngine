#pragma once

#include <src/FrogEngine.hpp>

#include "Zombie.hpp"

namespace AnimationDemo
{

 class AnimationDemo : public fe::GameTemplate {
  private:
   Zombie* zombie;
   
  public:
   AnimationDemo();
   void Start() override;
   void Update(float _deltaTime) override;
   void Stop() override;
  };
}