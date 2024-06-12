#pragma once

#include <src/FrogEngine.hpp>

class Paddle : public fe::GameObject {
 private:
  fe::Key keyUp;
  fe::Key keyDown;

  static const float MOVE_SPEED;
  
  float baseX;

 public:
  explicit Paddle(b2Vec2 _position, b2Rot _angle = b2Rot_identity);
  void SetControls(fe::Key _keyUp, fe::Key _keyDown);

  void Start() override;
  void Update(float _deltaTime) override;
};