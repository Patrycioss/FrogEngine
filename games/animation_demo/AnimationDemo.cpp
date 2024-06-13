#include "AnimationDemo.hpp"

namespace AnimationDemo
{
  AnimationDemo::AnimationDemo()
  {
	zombie = Instantiate<Zombie>(fe::Key::A, fe::Key::D);
  }

  void AnimationDemo::Start() {
  }

  void AnimationDemo::Update(float _deltaTime) {

  }

  void AnimationDemo::Stop() {

  }
}