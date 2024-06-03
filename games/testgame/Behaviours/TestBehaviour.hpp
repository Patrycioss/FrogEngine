﻿#pragma once

#include "src/FrogEngine.hpp"

 class TestBehaviour : public fe::Behaviour{
 public:
  TestBehaviour() = default;
  void Start() override;
  void Update(float _deltaTime) override;
  void Render() override;
  ~TestBehaviour() override;
};