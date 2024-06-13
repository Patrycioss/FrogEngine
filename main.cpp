#include "src/FrogEngine.hpp"
#include "games/game_demo/GameDemo.hpp"

int main() {
  fe::Engine::Initialize();
  GameDemo::GameDemo animationDemo;
  fe::Engine::Start(animationDemo);
  return 0;
}