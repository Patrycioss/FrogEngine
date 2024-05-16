#pragma once

#include "FrogEngine.hpp"

class Game final : public FrogEngine::IGame {
 public:
  explicit Game(FrogEngine::Engine& _engine);
  void Start() override;
  void Update(float _deltaTime) override;
  void Stop() override;
};
