#include "TestBehaviour.hpp"

void TestBehaviour::Start() {
  printf("Start test behaviour.");
}

void TestBehaviour::Update(float _deltaTime) {
  printf("Update test behaviour.");
}

void TestBehaviour::Render() {
  printf("Rendering test behaviour.");
}

TestBehaviour::~TestBehaviour() {
  printf("Destroying test behaviour.");
}