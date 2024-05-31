#include "src/FrogEngine.hpp"
#include "games/testgame/Game.hpp"
#include "games/pong/PongGame.hpp"

int main() {
  fe::Engine::Initialize();
  PongGame game;
  fe::Engine::Start(game);
  return 0;
}