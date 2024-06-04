#include "PongGame.hpp"

PongGame::PongGame() :
	paddleLeft(fe::Engine::Create<Paddle>(b2Vec2(200, 200))),
	paddleRight(fe::Engine::Create<Paddle>(b2Vec2(300, 300))),
	hasBeenPressed(false) {

  printf("Paddle left id: %i \n", paddleLeft->GetBody().index1);
  paddleLeft->SetControls(fe::Key::W, fe::Key::S);
  
  
  fe::Engine::SetGravity({0, 0});
}

void PongGame::Start() {

}

void PongGame::Update(float _deltaTime) {

//  printf("%i", (int)fe::Engine::IsKeyPressed(fe::Key::SPACE));

  if (fe::Engine::IsKeyPressed(fe::Key::SPACE) && !hasBeenPressed) {
	hasBeenPressed = true;
	printf("Destroying the PaddleLeft \n");
	fe::Engine::Destroy(paddleLeft);
  }

}

void PongGame::Stop() {

}


