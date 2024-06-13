#pragma once

#include <src/FrogEngine.hpp>

#include "Zombie.hpp"

namespace GameDemo
{

 class GameDemo : public fe::GameTemplate {
  private:
   Zombie* zombie;
   fe::GameObject* staticRect;
   
  public:
   GameDemo();
   void Start() override;
   void Update(float _deltaTime) override;
   void Stop() override;
  };
}