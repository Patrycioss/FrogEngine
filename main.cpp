#include "src/FrogEngine.hpp"
#include "games/testgame/Game.hpp"
#include "games/pong/PongGame.hpp"
#include "games/animation_demo/AnimationDemo.hpp"

int main() {
  fe::Engine::Initialize();
//  PongGame game;
  AnimationDemo::AnimationDemo game;
  fe::Engine::Start(game);
  return 0;
}