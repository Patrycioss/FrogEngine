#include "Game.hpp"

int main() {

  FrogEngine::Engine engine{};
  Game game{engine};
  engine.Start(&game);
  return 0;
}