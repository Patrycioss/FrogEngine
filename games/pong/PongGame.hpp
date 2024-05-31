#pragma once

#include "../../src/FrogEngine.hpp"
#include "Paddle.hpp"

class PongGame : public fe::GameTemplate {
  Paddle paddleLeft{{200,200}, b2MakeRot(90.0f)};
  Paddle paddleRight{{300,300}};
  
 public:
  void Start() override;
  void Update(float _deltaTime) override;
  void Stop() override;
};
