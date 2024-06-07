﻿#pragma once

#include <box2d/box2d.h>

namespace fe
{
  class Engine;

  class Box2DDebug {
	friend Engine;

   private:
	static b2DebugDraw debugDraw;
	static bool enabled;
	
	static void Initialize();
	static void SetDrawingBounds(const b2AABB& _bounds);

	static void DrawSolidPolygonCallback(b2Transform _transform, const b2Vec2* _vertices, int _vertexCount, float _radius, b2HexColor _color, void* _context);
	static void DrawPolygonCallback (const b2Vec2* _vertices, int _vertexCount, b2HexColor _colour, void* _context);

   public:
	static void Enable(bool _value = true);
	static bool IsEnabled();
  };
}


