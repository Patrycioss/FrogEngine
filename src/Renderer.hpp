#pragma once

#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <box2d/box2d.h>
#include <vector>

#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Colour.hpp"
#include "AnimationSettings.hpp"
#include "SpriteSettings.hpp"

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
	static ShaderRef animationShader;
	static Camera camera;
	
	static std::vector<Polygon> polygonsToDraw;
	
	static void InitializeSprite();
	
	static void Render();

   public:
	static void Initialize();
	
	
	// Rotation in radians.
	static void DrawSprite(Texture* _texture, ShaderRef _shader, const SpriteSettings& _spriteSettings);

	// Rotation in radians.
	static void DrawSprite(Texture* _texture, const SpriteSettings& _spriteSettings);
	
	static void DrawPolygon(b2Vec2* _vertices, int _vertexCount, Colour _colour = Colour::WHITE);
	
	static void DrawAnimationSprite(Texture* _texture, const AnimationSettings& _animationSettings, const SpriteSettings& _spriteSettings, float _timeSeconds);
	
	
	static void Cleanup();
  };
}