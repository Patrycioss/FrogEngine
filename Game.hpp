#pragma once

#include "src/FrogEngine.hpp"

class Game final : public FrogEngine::Engine {
 private:
  FrogEngine::Texture* texture = nullptr;
  FrogEngine::ShaderRef shader;
 public:
  explicit Game();
  void OnStart() override;
  void OnUpdate(float _deltaTime) override;
  void OnStop() override;
};
