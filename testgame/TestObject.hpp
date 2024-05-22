#pragma once

#include "../src/FrogEngine.hpp"
#include "Behaviours/TestBehaviour.hpp"

class TestObject : public fe::GameObject {
 private:
  TestBehaviour* testBehaviour;

 protected:
  void OnStart() override;
  void OnUpdate(float _deltaTime) override;

 public:
  TestObject();
  ~TestObject() override;

};
