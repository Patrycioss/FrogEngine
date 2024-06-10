#include "src/FrogEngine.hpp"
#include "games/pong/PongGame.hpp"
#include "games/animation_demo/AnimationDemo.hpp"

int main() {
  fe::Engine::Initialize();
  AnimationDemo::AnimationDemo animationDemo;
  fe::Engine::Start(animationDemo);
  return 0;
}