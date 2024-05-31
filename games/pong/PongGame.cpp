#include "PongGame.hpp"

void PongGame::Start() {

  fe::Engine::SetGravity({0, 1.0f});
  
  fe::Engine::RegisterObject(&paddleLeft);
  fe::Engine::RegisterObject(&paddleRight);
  
  paddleLeft.Start();
  paddleRight.Start();
}

void PongGame::Update(float _deltaTime) {
  
  paddleLeft.Update(_deltaTime);
  paddleRight.Update(_deltaTime);

}

void PongGame::Stop() {
  
}
