#include "src/core/Box2DDebug.hpp"
#include "src/core/Renderer.hpp"
#include "src/core/Engine.hpp"

namespace fe
{
  b2DebugDraw Box2DDebug::debugDraw{};
  bool Box2DDebug::enabled = false;

  void Box2DDebug::Initialize() {
	debugDraw.DrawSolidPolygon = DrawSolidPolygonCallback;
	debugDraw.DrawPolygon = DrawPolygonCallback;
	debugDraw.drawAABBs = true;
	debugDraw.drawShapes = true;
	debugDraw.drawingBounds = {{0, 0},
		{(float)fe::Engine::GetCurrentSettings().windowWidth, (float)fe::Engine::GetCurrentSettings().windowHeight}};
	debugDraw.useDrawingBounds = true;
  }

  void Box2DDebug::SetDrawingBounds(const b2AABB& _bounds) {
	debugDraw.drawingBounds = _bounds;
  }

  void Box2DDebug::DrawSolidPolygonCallback(b2Transform _transform,
											const b2Vec2* _vertices,
											int _vertexCount,
											float _radius,
											b2HexColor _color,
											void* _context) {

	b2Vec2 vertices[_vertexCount];

	float windowWidth = fe::Engine::GetCurrentSettings().windowWidth;
	float windowHeight = fe::Engine::GetCurrentSettings().windowHeight;

	for (int i = 0; i < _vertexCount; i++) {
	  b2Vec2 pos = _vertices[i] + _transform.p;

	  vertices[i].x = 2 * pos.x / windowWidth - 1;
	  vertices[i].y = -(2 * pos.y / windowHeight - 1);
	}

	Renderer::DrawPolygon(vertices, _vertexCount, Colour::FromHex(_color));
  }

  void Box2DDebug::DrawPolygonCallback(const b2Vec2* _vertices, int _vertexCount, b2HexColor _colour, void* _context) {
	b2Vec2 vertices[_vertexCount];

	float windowWidth = fe::Engine::GetCurrentSettings().windowWidth;
	float windowHeight = fe::Engine::GetCurrentSettings().windowHeight;

	for (int i = 0; i < _vertexCount; i++) {
	  b2Vec2 pos = _vertices[i];

	  vertices[i].x = 2 * pos.x / windowWidth - 1;
	  vertices[i].y = -(2 * pos.y / windowHeight - 1);
	}

	Renderer::DrawPolygon(vertices, _vertexCount, Colour::FromHex(_colour));
  }

  void Box2DDebug::Enable(bool _value) {
	enabled = _value;
  }

  bool Box2DDebug::IsEnabled() {
	return enabled;
  }
}