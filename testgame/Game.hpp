#pragma once

#include "../src/FrogEngine.hpp"
#include "src/Camera.hpp"

class Game final : public fe::GameTemplate {
 private:
  fe::GameObject* gameObject{};
  fe::Texture* texture = nullptr;
  fe::ShaderRef shader{};
  fe::Scene scene;
  
  fe::Camera camera;

 public:
  explicit Game();
  void Start() override;
  void Update(float _deltaTime) override;
  void Stop() override;
};