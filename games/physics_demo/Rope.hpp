#pragma once

#include "RopeSegment.hpp"

namespace PhysicsDemo
{
  class Rope {
   private:
	std::vector<RopeSegment*> segments;
	std::vector<b2WeldJointDef> jointDefs;

   public:
	Rope(const b2BodyId& _anchorBody, const b2Vec2& _anchorPosition, int _length, float _ropeWidth, float _segmentLength);
	Rope(const b2Vec2& _anchorPosition, int _length, float _ropeWidth, float _segmentLength);
  };
}

