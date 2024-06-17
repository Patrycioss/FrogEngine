#pragma once

#include <src/FrogEngine.hpp>

namespace PhysicsDemo
{

 class MovablePlatform : public fe::GameObject{
  private:
   static constexpr float FORCE = 200000;
   
  protected:
   void Update(float _deltaTime) override;
   
  public:
   explicit MovablePlatform(b2Vec2 _position);
  };

} // PhysicsDemo