#include "src/FrogEngine.hpp"
#include "games/animation_demo/AnimationDemo.hpp"
#include "games/physics_demo/PhysicsDemo.hpp"

int main() {
  fe::Engine::Initialize();
//  AnimationDemo::AnimationDemo animationDemo;
  PhysicsDemo::PhysicsDemo physicsDemo;
  fe::Engine::Start(physicsDemo);
  return 0;
}