#pragma once

#include <src/FrogEngine.hpp>

 class Paddle : public fe::GameObject {
 private:
  fe::Texture* texture;
  
 public:
  Paddle(b2Vec2 _position, b2Rot _angle = b2Rot_identity);
  
  void OnStart() override;
  void OnUpdate(float _deltaTime) override;
  void Render() override;

};
