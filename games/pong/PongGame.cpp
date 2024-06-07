#include "PongGame.hpp"

PongGame::PongGame() :
	paddleLeft(fe::Engine::Create<Paddle>(b2Vec2(200, 200))),
	paddleRight(fe::Engine::Create<Paddle>(b2Vec2(300, 300))) {

  printf("Paddle left id: %i \n", paddleLeft->GetBody().index1);
  paddleLeft->SetControls(fe::Key::W, fe::Key::S);

  fe::Engine::SetWindowSize(800,800);
  fe::Engine::SetGravity({0, 0});
  fe::Box2DDebug::Enable();
}

void PongGame::Start() {
  fe::Engine::Destroy(paddleLeft);
}

void PongGame::Update(float _deltaTime) {

//  fe::Renderer::DrawRectangle({200, 200}, {50, 50}, fe::Colour::RED);

//  b2Vec2 vertices[]{{-0.5f,0.5f}, {0.5f,0.5f}, {0.5f,-0.5f}, {-0.5f,-0.5f}};
//  fe::Renderer::DrawPolygon(vertices, 4, fe::Colour::RED);

  if (fe::Input::GetKeyDown(fe::Key::SPACE)) {
	printf("going down \n");
  }

  if (fe::Input::GetKey(fe::Key::SPACE)) {
	printf("is down \n");
  }

  if (fe::Input::GetKeyUp(fe::Key::SPACE)) {
	printf("going up \n");
  }

//  if (fe::Input::GetAnyKeyDown()){
//	printf("any key! \n");
//  }


  if (fe::Input::GetMouseDown(fe::MouseButton::B1)) {
	b2Vec2 pos = fe::Input::GetMousePos();
	printf("position: %f, %f \n", pos.x, pos.y);
  }





//  if (fe::Input::GetKeyDown(fe::Key::SPACE)) {
//	printf("Destroying the PaddleLeft \n");
//	fe::Engine::Destroy(paddleLeft);
//  }

}

void PongGame::Stop() {

}


