#include "TestBehaviour.hpp"

void TestBehaviour::Start() {
  printf("Start test behaviour.\n");
}

void TestBehaviour::Update(float _deltaTime) {
//  printf("Update test behaviour.\n");
}

void TestBehaviour::Render() {
//  printf("Rendering test behaviour.\n");
}

TestBehaviour::~TestBehaviour() {
  printf("Destroying test behaviour.\n");
}