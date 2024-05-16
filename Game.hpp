#pragma once

#include "FrogEngine.hpp"

class Game final : public FrogEngine::IGame {
 private:
  FrogEngine::Texture* texture = nullptr;
  FrogEngine::ShaderRef shader;
 public:
  explicit Game(FrogEngine::Engine& _engine);
  void Start() override;
  void Update(float _deltaTime) override;
  void Stop() override;
};
