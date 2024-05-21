#pragma once

#include "../src/FrogEngine.hpp"

class Game final : public fe::GameTemplate {
 private:
  fe::GameObject* gameObject;
  fe::Texture* texture = nullptr;
  fe::ShaderRef shader;
 public:
  explicit Game();
  void Start() override;
  void Update(float _deltaTime) override;
  void Stop() override;
};