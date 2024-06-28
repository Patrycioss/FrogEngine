#include "World.hpp"

void fe::World::Step() {
  b2World_Step(id, timeStep, subStepCount);
}

void fe::World::Draw(b2DebugDraw& _debugDraw) {
  b2World_Draw(id, &_debugDraw);
}

fe::World::World() {
  worldDef.gravity = {0, 0};
  id = b2CreateWorld(&worldDef);
}

b2WorldDef& fe::World::GetDef() {
  return worldDef;
}

b2BodyId fe::World::CreateBody(const b2BodyDef& _bodyDef) {
  return b2CreateBody(id, &_bodyDef);
}

b2JointId fe::World::CreateJoint(const b2WeldJointDef& _b2WeldJointDef) {
  return b2CreateWeldJoint(id, &_b2WeldJointDef);
}

void fe::World::OverlapAABB(const b2AABB& aabb, const b2QueryFilter& filter, b2OverlapResultFcn* function, void* context) {
  b2World_OverlapAABB(id, aabb, filter, function, context);
}

fe::World::~World() {
  b2DestroyWorld(id);
}

//TEMPORARY
b2WorldId& fe::World::ID() {
  return id;
}
