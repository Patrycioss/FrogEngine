#include "TestComponent.hpp"

void TestComponent::Start() {
  printf("Start test behaviour.\n");
}

void TestComponent::Update(float _deltaTime) {
//  printf("Update test behaviour.\n");
}

void TestComponent::Render() {
//  printf("Rendering test behaviour.\n");
}

TestComponent::~TestComponent() {
  printf("Destroying test behaviour.\n");
}