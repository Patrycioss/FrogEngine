#include "src/core/Box2DDebug.hpp"

#include <cerrno>

#include "src/core/Renderer.hpp"
#include "src/core/Engine.hpp"

namespace fe
{
  b2DebugDraw Box2DDebug::debugDraw{};
  bool Box2DDebug::enabled = false;
  
  bool Box2DDebug::pointError = false;
  bool Box2DDebug::capsuleError = false;
  bool Box2DDebug::solidCapsuleError = false;
  bool Box2DDebug::circleError = false;
  bool Box2DDebug::solidCircleError = false;
  bool Box2DDebug::segmentError = false;
  bool Box2DDebug::stringError = false;
  bool Box2DDebug::transformError = false;

  void Box2DDebug::Initialize() {
	debugDraw.DrawSolidPolygon = DrawSolidPolygonCallback;
	debugDraw.DrawPolygon = DrawPolygonCallback;
	debugDraw.DrawPoint = DrawPoint;
	debugDraw.DrawCapsule = DrawCapsule;
	debugDraw.DrawCircle = DrawCircle;
	debugDraw.DrawSegment = DrawSegment;
	debugDraw.DrawSolidCapsule = DrawSolidCapsule;
	debugDraw.DrawSolidCircle = DrawSolidCircle;
	debugDraw.DrawString = DrawString;
	debugDraw.DrawTransform = DrawTransform;
	debugDraw.drawAABBs = false;
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

  void Box2DDebug::DrawPoint(b2Vec2, float, b2HexColor, void*) {
	
	if (!pointError){
	  pointError = true;
	  perror("Draw point in Box2DDebug has not been implemented yet!");
	}
	
  }

  void Box2DDebug::DrawCapsule(b2Vec2, b2Vec2, float, b2HexColor, void*) {
	if (!capsuleError){
	  capsuleError = true;
	  perror("Draw capsule in Box2DDebug has not been implemented yet!");
	}
  }

  void Box2DDebug::DrawSolidCapsule(b2Vec2, b2Vec2, float, b2HexColor, void*) {
	if (!solidCapsuleError){
	  solidCapsuleError = true;
	  perror("Draw solid capsule in Box2DDebug has not been implemented yet!");
	}
  }

  void Box2DDebug::DrawCircle(b2Vec2, float, b2HexColor, void*) {
	if (!circleError){
	  circleError = true;
	  perror("Draw circle error in Box2DDebug has not been implemented yet!");
	}
  }

  void Box2DDebug::DrawSolidCircle(b2Transform, float, b2HexColor, void*) {
	if (!solidCircleError){
	  solidCircleError = true;
	  perror("Draw solid circle in Box2DDebug has not been implemented yet!");
	}
  }

  void Box2DDebug::DrawSegment(b2Vec2, b2Vec2, b2HexColor, void*) {
	if (!segmentError){
	  segmentError = true;
	  perror("Draw segment in Box2DDebug has not been implemented yet!");
	}
  }

  void Box2DDebug::DrawString(b2Vec2, const char*, void*) {
	if (!stringError){
	  stringError = true;
	  perror("Draw string in Box2DDebug has not been implemented yet!");
	}
  }

  void Box2DDebug::DrawTransform(b2Transform, void*) {
	if (!transformError){
	  transformError = true;
	  perror("Draw transform in Box2DDebug has not been implemented yet!");
	}
  }

  bool Box2DDebug::IsEnabled() {
	return enabled;
  }
  
  bool Box2DDebug::IsAABBEnabled() {
	return debugDraw.drawAABBs;
  }

  bool Box2DDebug::IsShapesEnabled() {
	return debugDraw.drawShapes;
  }

  void Box2DDebug::Enable(bool _value) {
	enabled = _value;
  }

  void Box2DDebug::EnableAABB(bool _value) {
	debugDraw.drawAABBs = _value;
  }

  void Box2DDebug::EnableShapes(bool _value) {
	debugDraw.drawShapes = _value;
  }
}