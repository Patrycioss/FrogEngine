#include "src/FrogEngine.hpp"
#include "testgame/Game.hpp"

int main() {
  Game game{};
  fe::Engine::Initialize(game);
  return 0;
}