#include "Rope.hpp"

namespace PhysicsDemo
{
  Rope::Rope(const b2BodyId& _anchorBody, const b2Vec2& _anchorPosition, int _length, float _ropeWidth, float _segmentLength) :
	  segments(), jointDefs() {

	segments.reserve(_length);
	jointDefs.reserve(_length);

	float halfSegmentLength = _segmentLength / 2.0f;

	for (int i = 0; i < _length; i++) {
	  
	  b2WeldJointDef& weldJointDef = jointDefs.emplace_back(b2DefaultWeldJointDef());
	  RopeSegment* anchorSegment =
		  fe::Engine::Instantiate<RopeSegment>(b2Vec2(_ropeWidth, _segmentLength), b2Body_GetPosition(_anchorBody) + _anchorPosition);
	  segments.push_back(anchorSegment);

	  if (i == 0) {
		weldJointDef.bodyIdA = _anchorBody;
		weldJointDef.localAnchorA = _anchorPosition;
	  } else {
		weldJointDef.bodyIdA = segments[i - 1]->GetBody();
		weldJointDef.localAnchorA = b2Vec2(0, halfSegmentLength);
	  }

	  weldJointDef.localAnchorB = b2Vec2(0, -halfSegmentLength);
	  weldJointDef.bodyIdB = anchorSegment->GetBody();
	  weldJointDef.collideConnected = true;
	  weldJointDef.angularHertz = 60;
	  weldJointDef.linearHertz = 60;

	  b2CreateWeldJoint(fe::Engine::GetWorldId(), &weldJointDef);
	}
  }

  Rope::Rope(const b2Vec2& _anchorPosition, int _length, float _ropeWidth, float _segmentLength):
	  segments(), jointDefs() {

	segments.reserve(_length);
	jointDefs.reserve(_length);

	float halfSegmentLength = _segmentLength / 2.0f;
	
	b2BodyId anchorBody = fe::Engine::Instantiate<fe::GameObject>(b2_staticBody, _anchorPosition)->GetBody(); 
	

	for (int i = 0; i < _length; i++) {

	  b2WeldJointDef& weldJointDef = jointDefs.emplace_back(b2DefaultWeldJointDef());
	  RopeSegment* anchorSegment =
		  fe::Engine::Instantiate<RopeSegment>(b2Vec2(_ropeWidth, _segmentLength), b2Body_GetPosition(anchorBody) + _anchorPosition);
	  segments.push_back(anchorSegment);

	  if (i == 0) {
		weldJointDef.bodyIdA = anchorBody;
		weldJointDef.localAnchorA = _anchorPosition;
		weldJointDef.collideConnected = false;
	  } else {
		weldJointDef.bodyIdA = segments[i - 1]->GetBody();
		weldJointDef.localAnchorA = b2Vec2(0, halfSegmentLength);
		weldJointDef.collideConnected = true;
	  }

	  weldJointDef.localAnchorB = b2Vec2(0, -halfSegmentLength);
	  weldJointDef.bodyIdB = anchorSegment->GetBody();
	  weldJointDef.angularHertz = 60;
	  weldJointDef.linearHertz = 60;

	  b2CreateWeldJoint(fe::Engine::GetWorldId(), &weldJointDef);
	}
  }
};