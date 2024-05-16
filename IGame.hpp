#pragma once

#include <box2d/box2d.h>

namespace FrogEngine
{
  class Engine;
}

namespace FrogEngine
{
  class IGame {
   protected:
	b2World world;
	Engine& engine;

	explicit IGame(Engine& _engine, b2Vec2 _gravity) : engine(_engine), world(_gravity) {};

   public:
	virtual void Start() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void Stop() = 0;

	b2World& World = world;
  };
}