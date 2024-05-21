#include "src/FrogEngine.hpp"
#include "testgame/Game.hpp"

int main() {
  Game game{};
  fe::Engine::Init(game);
  return 0;
}