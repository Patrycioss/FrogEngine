#pragma once

#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <box2d/box2d.h>
#include <vector>

#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Colour.hpp"

namespace fe
{
  class Engine;
  
  class Renderer {
	friend Engine;
   private:
	struct Polygon{
	  std::vector<b2Vec2> Vertices{};
	  Colour Colour = fe::Colour::WHITE;
	};
	
	static uint32_t spriteVAO;
	
	static ShaderRef spriteShader;
	static ShaderRef shapeShader;
	static Camera camera;
	
	static std::vector<Polygon> polygonsToDraw;
	
	static void InitializeSprite();
	
	static void Render();

   public:
	static void Initialize();
	
	
	// Rotation in radians.
	static void DrawSprite(Texture* _texture, ShaderRef _shader, b2Vec2 _position,
						   b2Vec2 _size = {10.0f, 10.0f}, float _rotate = 0.0f,
						   Colour _colour = {255, 255, 255});

	// Rotation in radians.
	static void DrawSprite(Texture* _texture, b2Vec2 _position,
						   b2Vec2 _size = {10.0f, 10.0f}, float _rotate = 0.0f,
						   Colour _colour = {255, 255, 255});
	
	static void DrawPolygon(b2Vec2* _vertices, int _vertexCount, Colour _colour = Colour::WHITE);
	
	
	static void Cleanup();
  };
}