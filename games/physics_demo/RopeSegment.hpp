#pragma once

#include "src/FrogEngine.hpp"

namespace PhysicsDemo
{
  class RopeSegment : public fe::GameObject {
   public:
	explicit RopeSegment(b2Vec2 _size, b2Vec2 _position);
  };
}