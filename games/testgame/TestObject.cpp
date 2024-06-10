﻿#include "TestObject.hpp"

TestObject::TestObject() : fe::GameObject(b2_staticBody) {
  testBehaviour = AddComponent<TestComponent>();
  std::cout << "Test Object Constructed \n";
  
  texture = fe::ResourceManager::LoadTexture("resources/textures/awesomeface.png");
}

void TestObject::OnStart() {
  std::cout << "Test Object Start \n";
}

void TestObject::OnUpdate(float _deltaTime) {
//  std::cout << "Test Object Update \n";
}

TestObject::~TestObject() {
  std::cout << "Test Object Destroy \n";
}