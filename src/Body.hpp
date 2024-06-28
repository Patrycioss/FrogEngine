#pragma once
#include <box2d/box2d.h>

namespace fe
{
  class Engine;
  
  class Body {
	friend Engine;
   private:
	b2BodyId id{};
	b2BodyDef bodyDef = b2DefaultBodyDef();

   public:
	explicit Body(const b2Vec2& _position, const b2BodyType& _bodyType);
	Body& operator=(const Body& _body) = delete;
	~Body();

	/**
 	 * @return The position of the Body. 
 	 */
	[[nodiscard]] b2Vec2 GetPosition() const;

	/**
	 * @return The rotation as a b2Rot of the Body. 
	 */
	[[nodiscard]] b2Rot GetRotation() const;

	/**
	 * @return The rotation of the Body as an angle in radians. 
	 */
	[[nodiscard]] float GetAngle() const;

	/**
     * Sets the transform of the Body.
 	 * @param _position The new position as a 2D vector.
 	 * @param _angle The new rotation as an angle in radians. 
 	 */
	void SetTransform(const b2Vec2& _position, float _angle);

	/**
	 * Sets the transform of the Body.
	 * @param _position The new position as a 2D vector.
	 * @param _rotation The new rotation as a b2Rot.
	 */
	void SetTransform(const b2Vec2& _position, const b2Rot& _rotation);

	/**
	 * Sets the position of the Body.
	 * @param _position A 2D vector for the new position.
	 */
	void SetPosition(const b2Vec2& _position);

	/**
	 * Sets the rotation of the Body.
	 * @param _angle The new rotation as an angle in radians.
	 */
	void SetAngle(float _angle);

	/**
	 * Sets the rotation of the Body.
	 * @param _rotation The new rotation as a b2Rot.
	 */
	void SetRotation(const b2Rot& _rotation);
	
	/**
	 * Adds a Box2D shape to the Body.
	 * @param _shapeDef Contains information mostly used for physics simulation.
	 * @param _polygon The actual shape of the shape :)
	 * @return The b2ShapeId associated with the shape.
	 */
	b2ShapeId AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon);
  };
}