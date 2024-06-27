#pragma once
#include <box2d/box2d.h>

namespace fe
{
  class Engine;

  /**
   * Wrapper class around Box2D's world.
   */
  class World {
	friend Engine;

   private:
	b2WorldId id{};
	b2WorldDef worldDef = b2DefaultWorldDef();
	float timeStep = 1.0f / 60.0f;
	int subStepCount = 4;

	void Step();
	void Draw(b2DebugDraw& _debugDraw);

   public:
	explicit World();
	~World();
	World& operator=(const World& _world) = delete;
	
	/**
	 * @return The definition of the world. 
	 */
	b2WorldDef& GetDef();
	
	/**
	 * According to the Box2D documentation:
	 * Generally physics engines for games like a time step at least as fast as 60Hz or 1/60 seconds. 
	 * You can get away with larger time steps, but you will have to be more careful about setting up your simulation. 
	 * It is also not good for the time step to vary from frame to frame. 
	 * A variable time step produces variable results, which makes it difficult to debug. 
	 * So don't tie the time step to your frame rate.
	 */
	void SetTimeStep(float _timeStep);
	
	/**
	 * According to the Box2D documentation:
	 * Box2D uses sub-stepping as a means of constraint iteration. 
	 * It lets the simulation move forward in time by small amounts and each constraint gets a chance to react to the changes.
	 * The suggested sub-step count for Box2D is 4. 
	 * You can tune this number to your liking, just keep in mind that this has a trade-off between performance and accuracy. 
	 * Using fewer sub-steps increases performance but accuracy suffers. 
	 * Likewise, using more sub-steps decreases performance but improves the quality of your simulation.
	 */
	void SetSubStepCount(float _subStepCount);

	/**
	 * Creates a body.
	 * @param _bodyDef Definition of the body.
	 * @return A b2BodyId that can be used to alter the created body.
	 */
	[[nodiscard]] b2BodyId CreateBody(const b2BodyDef& _bodyDef);

	/**
	 * Creates a weld joint.
	 * @param _b2WeldJointDef Definition of the weld joint.
	 * @return A b2JointId that can be used to alter the created joint.
	 */
	[[nodiscard]] b2JointId CreateJoint(const b2WeldJointDef& _b2WeldJointDef);

	/**
	 * Allows for querying for shapes that are within the specified boundary. 
	 * @param aabb The boundary in which to check for shapes.
	 * @param filter A filter of what shapes to check for.
	 * @param function A function that will be called whenever it finds an eligible shape.
	 * @param context The user context.
	 */
	void OverlapAABB(const b2AABB& aabb, const b2QueryFilter& filter, b2OverlapResultFcn* function, void* context);
  };
}


