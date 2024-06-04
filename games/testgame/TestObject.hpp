#pragma once

#include "src/FrogEngine.hpp"
#include "games/testgame/Components/TestComponent.hpp"

class TestObject : public fe::GameObject {
 private:
  TestComponent* testBehaviour;
  fe::Texture* texture;

 protected:
  void OnStart() override;
  void OnUpdate(float _deltaTime) override;

 public:
  TestObject();
  ~TestObject() override;

};
