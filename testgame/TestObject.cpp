#include "TestObject.hpp"

TestObject::TestObject() {
  testBehaviour = AddBehaviour<TestBehaviour>();
  std::cout << "Test Object Constructed \n";
}

void TestObject::OnStart() {
  std::cout << "Test Object Start \n";
}

void TestObject::OnUpdate(float _deltaTime) {
  std::cout << "Test Object Update \n";
}

TestObject::~TestObject() {
  std::cout << "Test Object Destroy \n";
}
