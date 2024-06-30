#pragma once

#include <box2d/box2d.h>

namespace fe
{
  class Engine;

  /**
   * Allows for drawing the debug information that Box2D provides.
   */
  class Box2DDebug {
	friend Engine;

   private:
	// Delete constructors
	Box2DDebug() = delete;
	Box2DDebug(Box2DDebug& _box2DDebug) = delete;
	Box2DDebug(Box2DDebug&& _box2DDebug) = delete;

	static b2DebugDraw debugDraw;
	static bool enabled;

	static void Initialize();
	static void SetDrawingBounds(const b2AABB& _bounds);

	static void DrawSolidPolygonCallback(b2Transform _transform,
										 const b2Vec2* _vertices,
										 int _vertexCount,
										 float _radius,
										 b2HexColor _color,
										 void* _context);
	static void DrawPolygonCallback(const b2Vec2* _vertices, int _vertexCount, b2HexColor _colour, void* _context);

	static bool pointError, capsuleError, solidCapsuleError, circleError, solidCircleError, segmentError, stringError, transformError;

	static void DrawPoint(b2Vec2, float, b2HexColor, void*);
	static void DrawCapsule(b2Vec2, b2Vec2, float, b2HexColor, void*);
	static void DrawSolidCapsule(b2Vec2, b2Vec2, float, b2HexColor, void*);
	static void DrawCircle(b2Vec2, float, b2HexColor, void*);
	static void DrawSolidCircle(b2Transform, float, b2HexColor, void*);
	static void DrawSegment(b2Vec2, b2Vec2, b2HexColor, void*);
	static void DrawString(b2Vec2, const char*, void*);
	static void DrawTransform(b2Transform, void*);
	
   public:
	
	/**
	 * @return Whether drawing of the Box2D debug information is enabled.
	 */
	static bool IsEnabled();

	/**
	 * @return Whether drawing of AABBs is enabled.
	 */
	static bool IsAABBEnabled();

	/**
	 * @return Whether drawing of shapes is enabled. 
	 */
	static bool IsShapesEnabled();

	/**
	 * Enables or disables drawing of the Box2D debug information.
	 * By default it's disabled.
	 */
	static void Enable(bool _value = true);

	/**
	 * Enables or disables drawing of AABBs.
	 */
	static void EnableAABB(bool _value = true);

	/**
 	 * Enables or disables drawing of shapes.
 	 */
	static void EnableShapes(bool _value = true);
  };
}


