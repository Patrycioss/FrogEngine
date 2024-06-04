#pragma once

#include "src/FrogEngine.hpp"

 class TestComponent : public fe::Component{
 public:
  TestComponent() = default;
  void Start() override;
  void Update(float _deltaTime) override;
  void Render() override;
  ~TestComponent() override;
};
