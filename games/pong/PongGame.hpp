#pragma once

#include "../../src/FrogEngine.hpp"
#include "Paddle.hpp"

class PongGame : public fe::GameTemplate {
  Paddle* paddleLeft;
  Paddle* paddleRight;
  
  bool hasBeenPressed;
  
 public:
  PongGame();
  void Start() override;
  void Update(float _deltaTime) override;
  void Stop() override;
};
