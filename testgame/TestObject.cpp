#include "TestObject.hpp"

TestObject::TestObject() {
  testBehaviour = AddBehaviour<TestBehaviour>();
  std::cout << "Test Object Constructed \n";
  
  texture = fe::ResourceManager::LoadTexture("resources/textures/awesomeface.png");
}

void TestObject::OnStart() {
  std::cout << "Test Object Start \n";
}

void TestObject::OnUpdate(float _deltaTime) {
//  std::cout << "Test Object Update \n";
  
  fe::SpriteRenderer::DrawSprite(texture, Transform.Position, {512,512});
}

TestObject::~TestObject() {
  std::cout << "Test Object Destroy \n";
}