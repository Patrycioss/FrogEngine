#pragma once

#include <src/FrogEngine.hpp>

#include "games/physics_demo/Rope.hpp"
#include "Zombie.hpp"

namespace PhysicsDemo
{
 class PhysicsDemo : public fe::GameTemplate {
  public:
   PhysicsDemo();
   void Start() override;
   void Update(float _deltaTime) override;
   void Stop() override;
  };
}